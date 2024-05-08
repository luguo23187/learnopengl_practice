# version 330 core
out vec4 FragColor;

struct Material{
	sampler2D diffuse; // ����Ҳ�Ƴ��˻����������ɫ��������Ϊ��������ɫ�ڼ�����������¶�������������ɫ
	sampler2D specular;
	sampler2D emission;
	float shininess;
};


struct DirLight{ // �����
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight{ // ���Դ
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct SpotLight{ // �۹�
	vec3 direction;
	vec3 position;

	float cutOff;
	float outerCutOff;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

// uniform vec3 objectColor;
// uniform vec3 lightColor;
// uniform vec3 lightPos;


in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

#define NR_POINT_LIGHTS 4 // NR_POINT_LIGHTS������������һ��PointLight�ṹ�������

uniform vec3 viewPos;
uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main(){
	// ����
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);

	// 1. �����
	vec3 result = CalcDirLight(dirLight, norm, viewDir);
	// 2. ���Դ
	for(int i = 0; i < NR_POINT_LIGHTS; i++)
		result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
	// 3. �۹�
	result += CalcSpotLight(spotLight, norm, FragPos, viewDir);

	FragColor = vec4(result, 1.0);
}


vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir){
	vec3 lightDir = normalize(-light.direction);
	// ��������ɫ
	float diff = max(dot(normal, lightDir), 0.0);
	// �������ɫ
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	// �ϲ����
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
	return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir){
	vec3 lightDir = normalize(light.position - fragPos);
	// ��������ɫ
	float diff = max(dot(normal, lightDir), 0.0);
	// �������ɫ
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	// ˥�����
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
	// �ϲ����
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
	ambient  *= attenuation;
	diffuse  *= attenuation;
	specular *= attenuation;
	return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir){
	vec3 lightDir = normalize(light.position - fragPos);
	// ��������ɫ
	float diff = max(dot(normal, lightDir), 0.0);
	// �������ɫ
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	// ˥�����
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
	// �۹��Ե˥��
	float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = (light.cutOff - light.outerCutOff);
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
	// �ϲ����
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
	ambient  *= attenuation;
	diffuse  *= attenuation * intensity;
	specular *= attenuation * intensity;

	return (ambient + diffuse + specular);
}


// void main()
// {
// 	// ������
// 	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
// 
// 	// ������
// 	vec3 norm = normalize(Normal);
// 	vec3 lightDir = normalize(light.position - FragPos);
// 	// vec3 lightDir = normalize(-light.direction);
// 	float diff = max(dot(norm, lightDir), 0.0);
// 	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
// 
// 	// �����
// 	vec3 viewDir = normalize(viewPos - FragPos);
// 	vec3 reflectDir = reflect(-lightDir, norm); // reflect����Ҫ���һ�������Ǵӹ�Դָ��Ƭ��λ�õ�����������lightDir��ǰ�����෴���Ǵ�Ƭ��ָ���Դ
// 	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess); //���32�Ǹ߹�ķ����(Shininess)��һ������ķ����Խ�ߣ�����������Խǿ��ɢ���Խ�٣��߹��ͻ�ԽС��
// 	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords)); 
// 
// 	// ����
// 	// vec3 emission = vec3(texture(material.emission, TexCoords));
// 
// 	// ���Դ˥��
// 	float distance = length(light.position - FragPos);
// 	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
// 	ambient *= attenuation;
// 	diffuse *= attenuation;
// 	specular *= attenuation;
// 
// 	// �۹⣬ ����Բ׶ʱ��˥��
// 	float theta = dot(lightDir, normalize(-light.direction));
// 	float epsilon = light.cutOff - light.outerCutOff;
// 	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0); // ע������ʹ����clamp���������ѵ�һ������Լ��(Clamp)����0.0��1.0֮�䡣�Ᵽ֤ǿ��ֵ������[0, 1]����֮�⡣
// 
// 	// �����Ի���������Ӱ�죬������������һ���
// 	diffuse *= intensity;
// 	specular *= intensity;
// 
// 	vec3 result = ambient + diffuse + specular;
// 	FragColor = vec4(result, 1.0);
// }