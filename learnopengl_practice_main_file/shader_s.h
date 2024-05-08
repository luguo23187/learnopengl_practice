#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
	//程序ID
	unsigned int ID;

	//读取并构建着色器
	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
	Shader(const char* vertexShaderPath, const char* fragmentShaderPath, const char* geometryShaderPath);

	//激活程序
	void use();

	//删除工程
	void deleteprogram();

	//uniform工具函数
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec2(const std::string& name, glm::vec2 value) const;
	void setVec3(const std::string& name, glm::vec3 value) const;
	void setVec3(const std::string& name, float value_r, float value_g, float value_b) const;
	void setMat4(const std::string& name, glm::mat4 value) const;
};


#endif