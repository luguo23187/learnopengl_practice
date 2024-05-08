#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture1;

void main()
{
	// 直接抛弃透明部分，无法呈现半透明效果
	// vec4 texColor = texture(texture1, TexCoords);
	// if(texColor.a < 0.1)
	// 	discard; // 抛弃透明的片段
	// FragColor = texColor;

	FragColor = texture(texture1, TexCoords);
}