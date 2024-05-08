
#pragma once

#include <glad/glad.h> // ����opengl����

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader_s.h"

#include <string>
#include <vector>

using namespace std;

// C++�ṹ����һ���ܰ������ԣ����ǵ��ڴ沼����������(Sequential)��Ҳ����˵��������ǽ��ṹ����Ϊһ����������ʹ�ã���ô��������˳�����нṹ��ı���
struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	// tangent
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;
};

struct Texture {
	unsigned int id;
	string type; // diffuse or specular
	string path;
};

class Mesh {
public:
	// ��������
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> texture;
	// ����
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> texture);
	void Draw(Shader shader);

	unsigned int VAO, VBO, EBO;

private:
	// ��Ⱦ����
	// unsigned int VAO, VBO, EBO;
	// ����
	void setupMesh(); //������setupMesh�����г�ʼ�����壬������ʹ��Draw��������������
};