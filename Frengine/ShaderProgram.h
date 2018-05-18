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

		void compileProgramFromFile(std::string vertFilePath, std::string fragFilePath);
		void compileDefaultProgram();

		GLuint getAttribLocation(std::string attribName);

		static void unuseShaders();

		void setUniformMat4(std::string uniformName, const glm::mat4& value);

		void use();
	private:
		GLuint _programID;

		GLuint _vertShaderID;
		GLuint _fragShaderID;

		void compileShaderFromString(std::string shaderText, GLuint shaderID);
		void compileProgramFromString(std::string vertShaderText, std::string fragShaderText);

		std::string loadTextFile(std::string filePath);
		

	};
}
