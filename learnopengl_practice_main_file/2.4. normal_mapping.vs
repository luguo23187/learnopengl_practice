#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;

out VS_OUT {
	vec3 FragPos;
	vec2 TexCoords;
	vec3 TangentLightPos;
	vec3 TangentViewPos;
	vec3 TangentFragPos;
} vs_out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform vec3 lightPos;
uniform vec3 viewPos;

void main(){
	gl_Position = projection * view * model * vec4(position, 1.0f);
	vs_out.FragPos = vec3(model * vec4(position, 1.0));
	vs_out.TexCoords = texCoords;

	// Ȼ�����Ǵ���ʵ�ʵ�TBN����ֱ�Ӱ���Ӧ������Ӧ�õ�mat3���������С�
	// ע�⣬�������ϣ������ȷ�Ļ��Ͳ�Ҫ��TBN��������model���󣬶���ʹ�÷��߾�����Ϊ����ֻ���������ķ��򣬲�����ƽ�ƺ����š�
	// vec3 T = normalize(vec3(model * vec4(tangent,   0.0)));
    // vec3 B = normalize(vec3(model * vec4(bitangent, 0.0)));
    // vec3 N = normalize(vec3(model * vec4(normal,    0.0)));

	// ���߾���
	mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 T = normalize(normalMatrix * tangent);
    vec3 B = normalize(normalMatrix * bitangent);
    vec3 N = normalize(normalMatrix * normal);  

	mat3 TBN = transpose(mat3(T, B, N)); // TBN����������
	vs_out.TangentLightPos = TBN * lightPos;
	vs_out.TangentViewPos  = TBN * viewPos;
    vs_out.TangentFragPos  = TBN * vs_out.FragPos;
}
/*
	������������TBN���������ʹ�����أ�ͨ����˵�����ַ�ʽʹ���������ǻ�������ַ�ʽ��˵��һ�£�

 1������ֱ��ʹ��TBN�������������԰���������ռ������ת������������ռ䡣
	������ǰ�������Ƭ����ɫ���У���ͨ�������õ��ķ������������TBN����ת������������ռ��У�
	�������з��ߺ��������ձ�������ͬһ������ϵ���ˡ�

 2������Ҳ����ʹ��TBN�������������������԰���������ռ������ת������������ռ䡣
	�������ʹ�������������������ձ�����������ת�������߿ռ䣬
	�������ߺ��������ձ�����һ����һ������ϵ���ˡ�
	����ΪlightPos��viewPos����ÿ��fragment���ж�Ҫ�ı䣬����fs_in.FragPos������Ҳ�����ڶ�����ɫ�������������߿ռ�λ�á���
	�����ڲ��ǰ�TBN�����������͸�������ɫ�������ǽ����߿ռ�Ĺ�Դλ�ã��۲�λ���Լ�����λ�÷��͸�������ɫ����
*/