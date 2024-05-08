#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoords;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform mat4 nullMatrix;

void main(){
	FragColor = (texture(texture1, TexCoords) * nullMatrix) + vec4(ourColor, 1.0);
}