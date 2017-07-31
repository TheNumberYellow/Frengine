#pragma once
#include <GL\glew.h>

#include <string>

namespace FR {
	class ShaderProgram {
	public:
		ShaderProgram();
		~ShaderProgram();

		void compileProgram(std::string vertFilePath, std::string fragFilePath);
		void use();
	private:
		GLuint _programID;

		GLuint _vertShaderID;
		GLuint _fragShaderID;

		void compileShader(std::string filePath, GLuint shaderID);

		const char* loadTextFile(std::string filePath);
	};
}
