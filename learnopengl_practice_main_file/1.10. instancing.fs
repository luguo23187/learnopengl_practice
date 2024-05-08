// #version 330 core
// out vec4 FragColor;
// 
// in vec3 fColor;
// 
// void main()
// {
//     FragColor = vec4(fColor, 1.0);
// }

#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

void main(){
	FragColor = texture(texture_diffuse1, TexCoords);
}