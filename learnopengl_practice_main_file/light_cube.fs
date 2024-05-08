# version 330 core
out vec4 FragColor;

struct Material{
	sampler2D diffuse; // 我们也移除了环境光材质颜色向量，因为环境光颜色在几乎所有情况下都等于漫反射颜色
	sampler2D specular;
	sampler2D emission;
	float shininess;
};


struct DirLight{ // 定向光
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight{ // 点光源
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct SpotLight{ // 聚光
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

#define NR_POINT_LIGHTS 4 // NR_POINT_LIGHTS常量来创建了一个PointLight结构体的数组

uniform vec3 viewPos;
uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main(){
	// 属性
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);

	// 1. 定向光
	vec3 result = CalcDirLight(dirLight, norm, viewDir);
	// 2. 点光源
	for(int i = 0; i < NR_POINT_LIGHTS; i++)
		result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
	// 3. 聚光
	result += CalcSpotLight(spotLight, norm, FragPos, viewDir);

	FragColor = vec4(result, 1.0);
}


vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir){
	vec3 lightDir = normalize(-light.direction);
	// 漫反射着色
	float diff = max(dot(normal, lightDir), 0.0);
	// 镜面光着色
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	// 合并结果
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
	return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir){
	vec3 lightDir = normalize(light.position - fragPos);
	// 漫反射着色
	float diff = max(dot(normal, lightDir), 0.0);
	// 镜面光着色
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	// 衰减结果
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
	// 合并结果
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
	// 漫反射着色
	float diff = max(dot(normal, lightDir), 0.0);
	// 镜面光着色
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	// 衰减结果
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
	// 聚光边缘衰减
	float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = (light.cutOff - light.outerCutOff);
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
	// 合并结果
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
// 	// 环境光
// 	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
// 
// 	// 漫反射
// 	vec3 norm = normalize(Normal);
// 	vec3 lightDir = normalize(light.position - FragPos);
// 	// vec3 lightDir = normalize(-light.direction);
// 	float diff = max(dot(norm, lightDir), 0.0);
// 	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
// 
// 	// 镜面光
// 	vec3 viewDir = normalize(viewPos - FragPos);
// 	vec3 reflectDir = reflect(-lightDir, norm); // reflect函数要求第一个向量是从光源指向片段位置的向量，但是lightDir当前正好相反，是从片段指向光源
// 	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess); //这个32是高光的反光度(Shininess)。一个物体的反光度越高，反射光的能力越强，散射得越少，高光点就会越小。
// 	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords)); 
// 
// 	// 发光
// 	// vec3 emission = vec3(texture(material.emission, TexCoords));
// 
// 	// 点光源衰减
// 	float distance = length(light.position - FragPos);
// 	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
// 	ambient *= attenuation;
// 	diffuse *= attenuation;
// 	specular *= attenuation;
// 
// 	// 聚光， 内外圆锥时间衰减
// 	float theta = dot(lightDir, normalize(-light.direction));
// 	float epsilon = light.cutOff - light.outerCutOff;
// 	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0); // 注意我们使用了clamp函数，它把第一个参数约束(Clamp)在了0.0到1.0之间。这保证强度值不会在[0, 1]区间之外。
// 
// 	// 将不对环境光做出影响，让它总是能有一点光
// 	diffuse *= intensity;
// 	specular *= intensity;
// 
// 	vec3 result = ambient + diffuse + specular;
// 	FragColor = vec4(result, 1.0);
// }