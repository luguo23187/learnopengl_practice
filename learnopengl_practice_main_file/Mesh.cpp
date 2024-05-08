#include "Mesh.h"

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> texture)
{
	this->vertices = vertices;
	this->indices = indices;
	this->texture = texture;

	setupMesh();
}

/*
	我们一开始并不知道这个网格（如果有的话）有多少纹理、纹理是什么类型的（在vector<Texture> texture中）。所以我们该如何在着色器中设置纹理单元和采样器呢？
	为了解决这个问题，我们需要设定一个命名标准：
		每个漫反射纹理被命名为texture_diffuseN，每个镜面光纹理应该被命名为texture_specularN，其中N的范围是1到纹理采样器最大允许的数字。
		比如说我们对某一个网格有3个漫反射纹理，2个镜面光纹理，它们的纹理采样器应该之后会被调用：
			uniform sampler2D texture_diffuse1;
			uniform sampler2D texture_diffuse2;
			uniform sampler2D texture_diffuse3;
			uniform sampler2D texture_specular1;
			uniform sampler2D texture_specular2;
*/

void Mesh::Draw(Shader shader)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	for (unsigned int i = 0; i < texture.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i); // 在绑定之前激活相应的纹理单元
		// 获取纹理序号(diffuse_textureN 中的 N)
		string number;
		string name = texture[i].type;
		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++);

		shader.setInt(("material." + name + number).c_str(), i); // diffuseNr 和 specularNr 是代表第几个此类型纹理，i是告知fragmentshader这个是激活的几号纹理
		glBindTexture(GL_TEXTURE_2D, texture[i].id); // texture[i].id 是loadTexture是生成的id
	}
	glActiveTexture(GL_TEXTURE0);

	// 绘制网格
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0); // （参数：类型三角形，三角形数目，  ，  ）
	glBindVertexArray(0);
}

void Mesh::setupMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// 顶点位置
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);
	// 顶点法线
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	glEnableVertexAttribArray(1);
	// 顶点纹理坐标
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
	glEnableVertexAttribArray(2);

	// 我们能够直接传入一大列的Vertex结构体的指针作为缓冲的数据，它们将会完美地转换为glBufferData所能用的参数：
	// 自然sizeof运算也可以用在结构体上来计算它的字节大小。这个应该是32字节的（8个float * 每个4字节）
	// 结构体的另外一个很好的用途是它的预处理指令offsetof(s, m)，它的第一个参数是一个结构体，第二个参数是这个结构体中变量的名字。
	// 这个宏会返回那个变量距结构体头部的字节偏移量(Byte Offset)。这正好可以用在定义glVertexAttribPointer函数中的偏移参数：

	glBindVertexArray(0);
}
