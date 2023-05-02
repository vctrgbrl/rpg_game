#include <iostream>
#include "Shader.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

using namespace Lone;

struct ShaderSource {
	std::string vertexShader;
	std::string fragmentShader;
};

ShaderSource ParseShaderSource(const char* sourcePath) {
	enum ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};
	std::ifstream stream(sourcePath);

	std::string line;

	std::string vertexSource;
	std::string fragmentSource;

	ShaderType state = ShaderType::NONE;

	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos) {
				state = ShaderType::VERTEX;
			}
			else if(line.find("fragment") != std::string::npos) {
				state = ShaderType::FRAGMENT;
			}
			continue;
		}
		switch (state)
		{
		case ShaderType::NONE:
			break;
		case ShaderType::VERTEX:
			vertexSource += line + '\n';
			break;
		case ShaderType::FRAGMENT:
			fragmentSource += line + '\n';
			break;
		default:
			break;
		}
		
	}
	
	return { vertexSource, fragmentSource };
}

Shader::Shader(const char* shaderPath) {
	
	ShaderSource source = ParseShaderSource(shaderPath);
	
	uint32_t vertexShader = CreateShader(source.vertexShader.c_str(), GL_VERTEX_SHADER);
	uint32_t fragmentShader = CreateShader(source.fragmentShader.c_str(), GL_FRAGMENT_SHADER);

	int success;
	char infoLog[512];
	u_int32_t shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	id = shaderProgram;
}

Shader::~Shader() {
	glDeleteProgram(id);
}

uint32_t Shader::CreateShader(const char* shaderSource, uint32_t shaderType) {
	uint32_t shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderSource, 0);
	glCompileShader(shader);

	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(shader, 512, 0, infoLog);
		if (shaderType == GL_VERTEX_SHADER) {
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
			std::cout << "Vertex: " << shaderSource << std::endl;
		} else if (shaderType == GL_FRAGMENT_SHADER) {
			std::cout << "ERROR::SHADER::FRAG::COMPILATION_FAILED\n" << infoLog << std::endl;
			std::cout << "Fragment: " << shaderSource << std::endl;
		}
	}
	return shader;
}

void Shader::Bind() {
	glUseProgram(id);
}

void Shader::setUniform(const char* name, bool value) {
	glUniform1i(glGetUniformLocation(id, name), (int)value); 
}

void Shader::setUniform(const char* name, int32_t value) {
	glUniform1i(glGetUniformLocation(id, name), value); 
}

void Shader::setUniform(const char* name, uint32_t value) {
	glUniform1ui(glGetUniformLocation(id, name), value); 
}

void Shader::setUniform(const char* name, float value) {
	glUniform1f(glGetUniformLocation(id, name), value); 
}

void Shader::setUniform(const char* name, glm::mat4& value) {
	glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setUniform(const char* name, glm::vec3& value) {
	glUniform3fv(glGetUniformLocation(id, name), 1, glm::value_ptr(value));
}