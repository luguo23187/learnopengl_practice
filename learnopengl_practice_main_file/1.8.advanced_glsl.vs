#version 330 core
layout (location = 0) in vec3 aPos;

// 将投影矩阵和视角矩阵储存在一个uniform块中、
// 在我们大多数的例子中，我们都会在每个渲染迭代中，对每个着色器设置projection和view Uniform矩阵。这是利用Uniform缓冲对象的一个非常完美的例子，
// 因为现在我们只需要存储这些矩阵一次就可以了。

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