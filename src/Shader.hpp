#ifndef SHADER_H
#define SHADER_H

#include <glm/glm.hpp>

namespace Lone {
	class Shader
	{
	public:
		Shader(const char* shaderPath);
		~Shader();
		void Bind();
		void setUniform(const char* name, bool value);
		void setUniform(const char* name, int32_t value);
		void setUniform(const char* name, uint32_t value);
		void setUniform(const char* name, float value);
		void setUniform(const char* name, glm::mat4& value);
		void setUniform(const char* name, glm::vec3& value);
	public:
		uint32_t id;
	private:
		uint32_t CreateShader(const char* shaderSource, uint32_t shaderType);
		uint32_t LinkProgram();
	};
}
#endif