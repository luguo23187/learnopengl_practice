// #version 330 core
// layout (location = 0) in vec2 aPos;
// layout (location = 1) in vec3 aColor;
// layout (location = 2) in vec2 aOffset;
// 
// out vec3 fColor;
// 
// // uniform vec2 offsets[100];
// 
// void main()
// {
//     // vec2 offset = offsets[gl_InstanceID]; // gl_instanceID, 从0开始，每次渲染都会递增1
//     vec2 offset = aOffset;
//     vec2 pos = aPos * (gl_InstanceID / 100.0);
//     gl_Position = vec4(pos + offset, 0.0, 1.0);
//     fColor = aColor;
// }

#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
	TexCoords = aTexCoords;
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	Normal = mat3(transpose(inverse(model))) * aNormal;
	FragPos = vec3(model * vec4(aPos, 1.0));
}