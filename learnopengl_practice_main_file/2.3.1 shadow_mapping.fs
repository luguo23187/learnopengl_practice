#version 330 core
out vec4 FragColor;

in VS_OUT{
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoords;
	vec4 FragPosLightSpace; // 光空间的片段位置
} fs_in;

uniform sampler2D diffuseTexture;
uniform sampler2D shadowMap; // 第一个渲染阶段得到的深度贴图

uniform vec3 lightPos;
uniform vec3 viewPos;

// 首先要检查一个片段是否在阴影中，把光空间片段位置转换为裁切空间的标准化设备坐标
// 当我们在顶点着色器输出一个裁切空间顶点位置到gl_Position时，OpenGL自动进行一个透视除法，将裁切空间坐标的范围-w到w转为-1到1
// 由于裁切空间的FragPosLightSpace并不会通过gl_Position传到片段着色器里，我们必须自己做透视除法：
float ShadowCalculation(vec4 fragPosLightSpace, vec3 normal, vec3 lightDir){
	// 执行透视除法
	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w; // 返回了片段在光空间的-1到1的范围。
	// projCoords的xyz分量都是[-1,1]（下面会指出这对于远平面之类的点才成立），
	// 而为了和深度贴图的深度相比较，z分量需要变换到[0,1]；
	// 为了作为从深度贴图中采样的坐标，xy分量也需要变换到[0,1]。所以整个projCoords向量都需要变换到[0,1]范围。
	projCoords = projCoords * 0.5 + 0.5;
	// 有了这些投影坐标，我们就能从深度贴图中采样得到0到1的结果
	float closestDepth = texture(shadowMap, projCoords.xy).r; // 我们将得到光的位置视野下最近的深度

	float currentDepth = projCoords.z; // 当前片段的深度

	float bias = max(0.5 * (1.0 - dot(normal, lightDir)), 0.005); // 阴影偏移，解决阴影失真的问题，黑色条纹；所有采样点都获得了比表面深度更小的深度值，这样整个表面就正确地被照亮，没有任何阴影
	// float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0; //简单检查currentDepth是否高于closetDepth，0是不在阴影中，1是在阴影中

	// 深度贴图有一个固定的分辨率，多个片段对应于一个纹理像素。结果就是多个片段会从深度贴图的同一个深度值进行采样，这几个片段便得到的是同一个阴影，这就会产生锯齿边。
	// PCF（percentage-closer filtering），这是一种多个不同过滤方式的组合，它产生柔和阴影，使它们出现更少的锯齿块和硬边
	// 核心思想是从深度贴图中多次采样，每一次采样的纹理坐标都稍有不同。每个独立的样本可能在也可能不再阴影中。所有的次生结果接着结合在一起，进行平均化，我们就得到了柔和阴影。
	float shadow = 0.0;
	vec2 texelSize = 1.0 / textureSize(shadowMap, 0); // 这个textureSize返回一个给定采样器纹理的0级mipmap的vec2类型的宽和高。用1除以它返回一个单独纹理像素的大小
													  // 我们用以对纹理坐标进行偏移，确保每个新样本，来自不同的深度值。
	for(int x = -1; x <= 1; x++){
		for(int y = -1; y <= 1; y++){
			float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
			shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
		}
	}
	shadow /= 9.0; 
	
	// 那里的坐标超出了光的正交视锥的远平面,当一个点比光的远平面还要远时，它的投影坐标的z坐标大于1.0
	if(currentDepth > 1.0){
		shadow = 0.0;
	}

	return shadow;
}

void main(){
	vec3 color = texture(diffuseTexture, fs_in.TexCoords).rgb;
	vec3 normal = normalize(fs_in.Normal);
	vec3 lightColor = vec3(1.0);
	// ambient
	vec3 ambient = 0.15 * color;
	// diffuse
	vec3 lightDir = normalize(lightPos - fs_in.FragPos);
	float diff = max(dot(lightDir, normal), 0.0);
	vec3 diffuse = diff * lightColor;
	// specular
	vec3 viewDir = normalize(viewPos - fs_in.FragPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = 0.0;
	vec3 halfwayDir = normalize(lightDir + viewDir);
	spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
	vec3 specular = spec * lightColor;
	// 计算阴影
	float shadow  = ShadowCalculation(fs_in.FragPosLightSpace, normal, lightDir);
	vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color; // 我们我们把diffuse和specular乘以(1-阴影元素)，这表示这个片段有多大成分不在阴影中。

	FragColor = vec4(lighting, 1.0f);
}