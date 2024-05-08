#version 330 core
layout (location = 0) in vec3 aPos;
// layout (location = 1) in vec2 aTexCoords;
layout (location = 1) in vec3 aNormal;

// out vec2 TexCoords;
out vec3 Position;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    // TexCoords = aTexCoords;
    // gl_Position = projection * view * model * vec4(aPos, 1.0);

    // 反射
    Normal = mat3(transpose(inverse(model))) * aNormal; 
    Position = vec3(model * vec4(aPos, 1.0)); // 输出向量是一个世界空间的位置向量,用于计算观察方向向量
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}