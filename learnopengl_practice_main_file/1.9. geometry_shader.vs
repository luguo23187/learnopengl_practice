#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

// out VS_OUT{
// 	// vec3 normal; 这是顶点的normal，需要的是面的normal，要直接算
// 	vec2 texCoords;
// } vs_out;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
	// vs_out.texCoords = aTexCoords;
	TexCoords = aTexCoords;
	gl_Position = projection * view * model * vec4(aPos, 1.0);
}