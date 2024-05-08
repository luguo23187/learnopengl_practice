#version 330 core

layout (location = 0) in vec3 aPos;
// layout (location = 1) in vec3 aColor; /* 3D时做的更改 */
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 clip_space;

void main()
{
   gl_Position = clip_space * vec4(aPos.x, aPos.y, aPos.z, 1.0);
   // ourColor = aColor;  /* 3D时做的更改 */
   TexCoord = aTexCoord;
}