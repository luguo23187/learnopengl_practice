#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture1;

void main()
{
	// ֱ������͸�����֣��޷����ְ�͸��Ч��
	// vec4 texColor = texture(texture1, TexCoords);
	// if(texColor.a < 0.1)
	// 	discard; // ����͸����Ƭ��
	// FragColor = texColor;

	FragColor = texture(texture1, TexCoords);
}