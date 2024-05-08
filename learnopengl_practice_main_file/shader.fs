#version 330 core

out vec4 FragColor;
// in vec3 ourColor; /* 3Dʱ���ĸ��� */
in vec2 TexCoord;

// uniform vec4 ourColor;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float rate;

void main()
{
    // FragColor = vec4(ourColor, 1.0);
    // GLSL�ڽ���texture�����������������ɫ������һ��������������������ڶ��������Ƕ�Ӧ���������ꡣ
    // texture������ʹ��֮ǰ���õ������������Ӧ����ɫֵ���в��������Ƭ����ɫ���������������ģ���ֵ�����������ϵ�(���˺��)��ɫ��
    // FragColor = texture(texture2, TexCoord);
    // ������ɫ���
    // FragColor = texture(texture1, TexCoord) * vec4(ourColor, 1.0);
    // ����������
    //FragColor = mix(texture(texture1, TexCoord),texture(texture2, TexCoord), 0.2);
    FragColor = mix(texture(texture1, TexCoord),texture(texture2, vec2(1.0 - TexCoord.x, TexCoord.y)), rate);
}