#pragma once
// 利用Model加载模型，这个教程的目标是创建另一个类来完整地表示一个模型，或者说是包含多个网格，甚至是多个物体的模型。

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "shader_s.h"
#include "Mesh.h"

#include "stb_image.h"

// 首先去检查它有没有被加载过。如果有的话，我们会直接使用那个纹理，并跳过整个加载流程，来为我们省下很多处理能力。
//struct Texture {
//	unsigned int id;
//	string type;
//	aiString path; // 我们储存纹理的路径用于与其它纹理进行比较
//};

class Model {
public:
	// 函数
	Model(string const& path);
	void Draw(Shader shader);
	vector<Mesh> meshes;

private:
	// 模型数据
	
	vector<Texture> textures_loaded; // 将所有加载过的纹理储存在另一个vector中，在模型类的顶部声明为一个私有变量
	string directory;
	// 函数
	void loadModel(string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
	unsigned int TextureFromFile(const char* path, const string& directory);
};