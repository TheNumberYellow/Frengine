#pragma once
#include <GL\glew.h>

#include <string>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

namespace FR {
	class ShaderProgram {
	public:
		ShaderProgram();
		~ShaderProgram();

		void compileProgram(std::string vertFilePath, std::string fragFilePath);
		GLuint getAttribLocation(std::string attribName);

		void setUniformMat4(std::string uniformName, const glm::mat4& value);

		void use();
	private:
		GLuint _programID;

		GLuint _vertShaderID;
		GLuint _fragShaderID;

		void compileShader(std::string filePath, GLuint shaderID);

		std::string loadTextFile(std::string filePath);
	};
}
