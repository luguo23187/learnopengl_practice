#include "Mesh.h"

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> texture)
{
	this->vertices = vertices;
	this->indices = indices;
	this->texture = texture;

	setupMesh();
}

/*
	����һ��ʼ����֪�������������еĻ����ж�������������ʲô���͵ģ���vector<Texture> texture�У����������Ǹ��������ɫ������������Ԫ�Ͳ������أ�
	Ϊ�˽��������⣬������Ҫ�趨һ��������׼��
		ÿ����������������Ϊtexture_diffuseN��ÿ�����������Ӧ�ñ�����Ϊtexture_specularN������N�ķ�Χ��1����������������������֡�
		����˵���Ƕ�ĳһ��������3������������2��������������ǵ����������Ӧ��֮��ᱻ���ã�
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
		glActiveTexture(GL_TEXTURE0 + i); // �ڰ�֮ǰ������Ӧ������Ԫ
		// ��ȡ�������(diffuse_textureN �е� N)
		string number;
		string name = texture[i].type;
		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++);

		shader.setInt(("material." + name + number).c_str(), i); // diffuseNr �� specularNr �Ǵ���ڼ�������������i�Ǹ�֪fragmentshader����Ǽ���ļ�������
		glBindTexture(GL_TEXTURE_2D, texture[i].id); // texture[i].id ��loadTexture�����ɵ�id
	}
	glActiveTexture(GL_TEXTURE0);

	// ��������
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0); // �����������������Σ���������Ŀ��  ��  ��
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

	// ����λ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);
	// ���㷨��
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	glEnableVertexAttribArray(1);
	// ������������
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
	glEnableVertexAttribArray(2);

	// �����ܹ�ֱ�Ӵ���һ���е�Vertex�ṹ���ָ����Ϊ��������ݣ����ǽ���������ת��ΪglBufferData�����õĲ�����
	// ��Ȼsizeof����Ҳ�������ڽṹ���������������ֽڴ�С�����Ӧ����32�ֽڵģ�8��float * ÿ��4�ֽڣ�
	// �ṹ�������һ���ܺõ���;������Ԥ����ָ��offsetof(s, m)�����ĵ�һ��������һ���ṹ�壬�ڶ�������������ṹ���б��������֡�
	// �����᷵���Ǹ�������ṹ��ͷ�����ֽ�ƫ����(Byte Offset)�������ÿ������ڶ���glVertexAttribPointer�����е�ƫ�Ʋ�����

	glBindVertexArray(0);
}
