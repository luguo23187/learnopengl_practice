
#pragma once

#include <glad/glad.h> // 调用opengl函数

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader_s.h"

#include <string>
#include <vector>

using namespace std;

// C++结构体有一个很棒的特性，它们的内存布局是连续的(Sequential)。也就是说，如果我们将结构体作为一个数据数组使用，那么它将会以顺序排列结构体的变量
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
	// 网格数据
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> texture;
	// 函数
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> texture);
	void Draw(Shader shader);

	unsigned int VAO, VBO, EBO;

private:
	// 渲染数据
	// unsigned int VAO, VBO, EBO;
	// 函数
	void setupMesh(); //我们在setupMesh函数中初始化缓冲，并最终使用Draw函数来绘制网格
};