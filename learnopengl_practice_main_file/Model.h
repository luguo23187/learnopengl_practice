#pragma once
// ����Model����ģ�ͣ�����̵̳�Ŀ���Ǵ�����һ�����������ر�ʾһ��ģ�ͣ�����˵�ǰ���������������Ƕ�������ģ�͡�

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "shader_s.h"
#include "Mesh.h"

#include "stb_image.h"

// ����ȥ�������û�б����ع�������еĻ������ǻ�ֱ��ʹ���Ǹ����������������������̣���Ϊ����ʡ�ºܶദ��������
//struct Texture {
//	unsigned int id;
//	string type;
//	aiString path; // ���Ǵ��������·������������������бȽ�
//};

class Model {
public:
	// ����
	Model(string const& path);
	void Draw(Shader shader);
	vector<Mesh> meshes;

private:
	// ģ������
	
	vector<Texture> textures_loaded; // �����м��ع�������������һ��vector�У���ģ����Ķ�������Ϊһ��˽�б���
	string directory;
	// ����
	void loadModel(string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
	unsigned int TextureFromFile(const char* path, const string& directory);
};