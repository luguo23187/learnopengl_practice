#version 330 core
out vec4 FragColor;

in VS_OUT{
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoords;
	vec4 FragPosLightSpace; // ��ռ��Ƭ��λ��
} fs_in;

uniform sampler2D diffuseTexture;
uniform sampler2D shadowMap; // ��һ����Ⱦ�׶εõ��������ͼ

uniform vec3 lightPos;
uniform vec3 viewPos;

// ����Ҫ���һ��Ƭ���Ƿ�����Ӱ�У��ѹ�ռ�Ƭ��λ��ת��Ϊ���пռ�ı�׼���豸����
// �������ڶ�����ɫ�����һ�����пռ䶥��λ�õ�gl_Positionʱ��OpenGL�Զ�����һ��͸�ӳ����������пռ�����ķ�Χ-w��wתΪ-1��1
// ���ڲ��пռ��FragPosLightSpace������ͨ��gl_Position����Ƭ����ɫ������Ǳ����Լ���͸�ӳ�����
float ShadowCalculation(vec4 fragPosLightSpace, vec3 normal, vec3 lightDir){
	// ִ��͸�ӳ���
	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w; // ������Ƭ���ڹ�ռ��-1��1�ķ�Χ��
	// projCoords��xyz��������[-1,1]�������ָ�������Զƽ��֮��ĵ�ų�������
	// ��Ϊ�˺������ͼ�������Ƚϣ�z������Ҫ�任��[0,1]��
	// Ϊ����Ϊ�������ͼ�в��������꣬xy����Ҳ��Ҫ�任��[0,1]����������projCoords��������Ҫ�任��[0,1]��Χ��
	projCoords = projCoords * 0.5 + 0.5;
	// ������ЩͶӰ���꣬���Ǿ��ܴ������ͼ�в����õ�0��1�Ľ��
	float closestDepth = texture(shadowMap, projCoords.xy).r; // ���ǽ��õ����λ����Ұ����������

	float currentDepth = projCoords.z; // ��ǰƬ�ε����

	float bias = max(0.5 * (1.0 - dot(normal, lightDir)), 0.005); // ��Ӱƫ�ƣ������Ӱʧ������⣬��ɫ���ƣ����в����㶼����˱ȱ�����ȸ�С�����ֵ�����������������ȷ�ر�������û���κ���Ӱ
	// float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0; //�򵥼��currentDepth�Ƿ����closetDepth��0�ǲ�����Ӱ�У�1������Ӱ��

	// �����ͼ��һ���̶��ķֱ��ʣ����Ƭ�ζ�Ӧ��һ���������ء�������Ƕ��Ƭ�λ�������ͼ��ͬһ�����ֵ���в������⼸��Ƭ�α�õ�����ͬһ����Ӱ����ͻ������ݱߡ�
	// PCF��percentage-closer filtering��������һ�ֶ����ͬ���˷�ʽ����ϣ������������Ӱ��ʹ���ǳ��ָ��ٵľ�ݿ��Ӳ��
	// ����˼���Ǵ������ͼ�ж�β�����ÿһ�β������������궼���в�ͬ��ÿ������������������Ҳ���ܲ�����Ӱ�С����еĴ���������Ž����һ�𣬽���ƽ���������Ǿ͵õ��������Ӱ��
	float shadow = 0.0;
	vec2 texelSize = 1.0 / textureSize(shadowMap, 0); // ���textureSize����һ�����������������0��mipmap��vec2���͵Ŀ�͸ߡ���1����������һ�������������صĴ�С
													  // �������Զ������������ƫ�ƣ�ȷ��ÿ�������������Բ�ͬ�����ֵ��
	for(int x = -1; x <= 1; x++){
		for(int y = -1; y <= 1; y++){
			float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
			shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
		}
	}
	shadow /= 9.0; 
	
	// ��������곬���˹��������׶��Զƽ��,��һ����ȹ��Զƽ�滹ҪԶʱ������ͶӰ�����z�������1.0
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
	// ������Ӱ
	float shadow  = ShadowCalculation(fs_in.FragPosLightSpace, normal, lightDir);
	vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color; // �������ǰ�diffuse��specular����(1-��ӰԪ��)�����ʾ���Ƭ���ж��ɷֲ�����Ӱ�С�

	FragColor = vec4(lighting, 1.0f);
}