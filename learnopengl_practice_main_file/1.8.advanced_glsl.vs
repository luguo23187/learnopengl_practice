#version 330 core
layout (location = 0) in vec3 aPos;

// ��ͶӰ������ӽǾ��󴢴���һ��uniform���С�
// �����Ǵ�����������У����Ƕ�����ÿ����Ⱦ�����У���ÿ����ɫ������projection��view Uniform������������Uniform��������һ���ǳ����������ӣ�
// ��Ϊ��������ֻ��Ҫ�洢��Щ����һ�ξͿ����ˡ�

layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};
uniform mat4 model;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}