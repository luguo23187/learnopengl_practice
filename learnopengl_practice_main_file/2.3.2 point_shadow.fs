#version 330 core
out vec4 FragColor;

in VS_OUT {
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoords;
} fs_in;

uniform sampler2D diffuseTexture;
uniform samplerCube depthMap;

uniform vec3 lightPos;
uniform vec3 viewPos;

uniform float far_plane;

/*
	��һЩϸ΢�Ĳ�ͬ�����մ���һ������������������һ��uniform����samplerCube��
	shadowCalculation������fragment��λ����Ϊ���Ĳ�����ȡ���˹�ռ��fragmentλ�á�
	�������ڻ�Ҫ��������׶��Զƽ��ֵ���������ǻ���Ҫ����
*/
/*
float ShadowCalculation(vec3 fragPos){
	// ��������ͼ����ȡ�������Ѿ��ӽ̵̳���������ͼ�����뵽�������Ѿ�����ȴ���Ϊfragment�͹�λ��֮��ľ�����(depthshadow��)
	vec3 fragToLight = fragPos - lightPos;
	float closestDepth = texture(depthMap, fragToLight).r;

	// closestDepthֵ������0��1�ķ�Χ���ˣ����������Ƚ���ת����0��far_plane�ķ�Χ������Ҫ��������far_plane��
	closestDepth *= far_plane;
	// ��ȡ��ǰfragment�͹�Դ֮������ֵ�����ǿ��Լ򵥵�ʹ��fragToLight�ĳ�������ȡ������ȡ����������μ�����������ͼ�е����ֵ��
	float currentDepth = length(fragToLight); //���ص��Ǻ�closestDepth��Χ��ͬ�����ֵ��

	float bias = 0.05; 
    float shadow = currentDepth -  bias > closestDepth ? 1.0 : 0.0;

    return shadow;

	// return closestDepth; // ֱ����ʾ�������ֵ������һ���Ҷȳ���
}
*/
// PCF�㷨�Ử��Ӱ
vec3 sampleOffsetDirections[20] = vec3[]
(
   vec3( 1,  1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1,  1,  1), 
   vec3( 1,  1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1,  1, -1),
   vec3( 1,  1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1,  1,  0),
   vec3( 1,  0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1,  0, -1),
   vec3( 0,  1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0,  1, -1)
);

float ShadowCalculation(vec3 fragPos){
	vec3 fragToLight = fragPos - lightPos;
	float currentDepth = length(fragToLight);

	float shadow = 0.0;
	float bias = 0.15;
	int sample = 20; // �����ķ�����20��
	float viewDistance = length(viewPos - fragPos);
	// float diskRadius = 0.05; // ���ǰ�һ��ƫ������ӵ�ָ����diskRadius�У�����fragToLight����������Χ����������ͼ�������
	float diskRadius = (1.0 + (viewDistance / far_plane)) / 25.0; 
	// ���ǿ��Ի��ڹ۲�����һ��fragment�ľ������ı�diskRadius���������Ǿ��ܸ��ݹ۲��ߵľ���������ƫ�ư뾶�ˣ��������Զ��ʱ����Ӱ����ͣ������˾͸�������
	for(int i = 0; i < sample; i++){
		float closestDepth = texture(depthMap, fragToLight + sampleOffsetDirections[i] * diskRadius).r;
		closestDepth *= far_plane; // ת����0��far_plane�ķ�Χ
		if(currentDepth - bias > closestDepth)
			shadow += 1.0;
	}
	shadow /= float(sample);

	return shadow;
}

void main(){
	vec3 color = texture(diffuseTexture, fs_in.TexCoords).rgb;
	vec3 normal = normalize(fs_in.Normal);
	vec3 lightColor = vec3(0.3);
	// ambient;
	vec3 ambient = 0.3 * color;
	// diffuse
	vec3 lightDir = normalize(lightPos - fs_in.FragPos);
	float diff = max(dot(lightDir, normal), 0.0);
	vec3 diffuse = diff * lightColor;
	// Specular
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    vec3 specular = spec * lightColor; 
	// Calculate shadow
    float shadow = ShadowCalculation(fs_in.FragPos);                      
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;    

    FragColor = vec4(lighting, 1.0f);
	// FragColor = vec4(vec3(shadow / far_plane), 1.0);
}