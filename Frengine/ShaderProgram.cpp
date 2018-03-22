#include "ShaderProgram.h"
#include <fstream>
#include <vector>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

using namespace FR;


ShaderProgram::ShaderProgram() {

}


ShaderProgram::~ShaderProgram() {
	glDeleteProgram(_programID);
}

void ShaderProgram::compileProgram(std::string vertFilePath, std::string fragFilePath) {\
	_programID = glCreateProgram();

	_vertShaderID = glCreateShader(GL_VERTEX_SHADER);
	_fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	compileShader(vertFilePath, _vertShaderID);
	compileShader(fragFilePath, _fragShaderID);

	// Attach shaders to program
	glAttachShader(_programID, _vertShaderID);
	glAttachShader(_programID, _fragShaderID);

	// Link program
	glLinkProgram(_programID);

	// Detach and delete shaders afterwards
	glDetachShader(_programID, _vertShaderID);
	glDetachShader(_programID, _fragShaderID);
	glDeleteShader(_vertShaderID);
	glDeleteShader(_fragShaderID);
}

GLuint FR::ShaderProgram::getAttribLocation(std::string attribName) {
	return glGetAttribLocation(_programID, attribName.c_str());
}

void FR::ShaderProgram::unuseShaders() {
	glUseProgram(0);
}

void FR::ShaderProgram::setUniformMat4(std::string uniformName, const glm::mat4& value) {
	glUniformMatrix4fv(glGetUniformLocation(_programID, uniformName.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::use() {
	glUseProgram(_programID);
}

void ShaderProgram::compileShader(std::string filePath, GLuint shaderID) {
	std::string shaderText = loadTextFile(filePath);

	const char* cStrShaderText = shaderText.c_str();

	glShaderSource(shaderID, 1, &cStrShaderText, NULL);
	glCompileShader(shaderID);

	GLint success = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	
	if (success == GL_FALSE) {
		GLint logLength;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);

		std::vector<char> errorLog(logLength);
		glGetShaderInfoLog(shaderID, logLength, &logLength, &(errorLog[0]));

		glDeleteShader(shaderID);

		std::printf("||| Compilation of shader %s failed, error log:\n%s\n", filePath.c_str(), &(errorLog[0]));
	}
}

std::string ShaderProgram::loadTextFile(std::string filePath) {
	std::ifstream file(filePath);

	if (file.fail()) {
		printf("Frengine Error: ShaderProgram Error: Could not find specified file %s\n", filePath.c_str());
		return nullptr;
	}

	std::string fileContents;
	std::string line;
	while (std::getline(file, line)) {
		fileContents += line + '\n';
	}

	file.close();
	
	return fileContents;
}