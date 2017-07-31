#include "ShaderProgram.h"
#include <fstream>
#include <vector>

using namespace FR;


ShaderProgram::ShaderProgram() {
	_programID = glCreateProgram();
}


ShaderProgram::~ShaderProgram() {
	glDeleteProgram(_programID);
}

void ShaderProgram::compileProgram(std::string vertFilePath, std::string fragFilePath) {
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

void ShaderProgram::use() {
	glUseProgram(_programID);
}

void ShaderProgram::compileShader(std::string filePath, GLuint shaderID) {
	const char* shaderText = loadTextFile(filePath);
	if (shaderText == nullptr) {
		return;
	}
	glShaderSource(shaderID, 1, &shaderText, NULL);
	glCompileShader(shaderID);

	GLint success = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	
	if (success == GL_FALSE) {
		GLint logLength;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);

		std::vector<char> errorLog(logLength);
		glGetShaderInfoLog(shaderID, logLength, &logLength, &(errorLog[0]));

		glDeleteShader(shaderID);

		std::printf("Compilation of shader %s failed, error log:\n%s\n", filePath, &(errorLog[0]));
	}


}

const char* ShaderProgram::loadTextFile(std::string filePath) {
	std::ifstream file(filePath);

	if (file.fail()) {
		printf("Frengine Error: ShaderProgram Error: Could not find specified file %s\n", filePath);
		return nullptr;
	}

	std::string fileContents;
	std::string line;
	while (std::getline(file, line)) {
		fileContents += line + '\n';
	}
	file.close();
	return fileContents.c_str();
}