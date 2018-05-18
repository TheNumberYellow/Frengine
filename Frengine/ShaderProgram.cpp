#include "ShaderProgram.h"
#include <fstream>
#include <vector>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <iostream>

using namespace FR;

static const std::string defaultFragShaderString = 
"#version 400\n"
"in vec2 fragmentUV;\n"
"out vec4 fragColour;\n"
"uniform sampler2D sampler;\n"
"void main() {\n"
"	vec4 colour = texture(sampler, fragmentUV);\n"
"	fragColour = colour;\n"
"}"
;

static const std::string defaultVertShaderString =
"#version 400\n"
"layout(location = 0) in vec3 vertexPosition;\n"
"layout(location = 1) in vec2 vertexUV;\n"
"out vec2 fragmentUV;\n"
"uniform mat4 projection;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"void main() {\n"
"	fragmentUV = vertexUV;\n"
"	//gl_Position = projection * view * model * vec4(vertexPosition, 1.0);\n"
"	gl_Position = projection * view * model * vec4(vertexPosition, 1.0);\n"
"}"
;

ShaderProgram::ShaderProgram() {

}


ShaderProgram::~ShaderProgram() {
	glDeleteProgram(_programID);
}

void ShaderProgram::compileProgramFromFile(std::string vertFilePath, std::string fragFilePath) {
	std::string vertShaderString = loadTextFile(vertFilePath);
	std::string fragShaderString = loadTextFile(fragFilePath);
	
	compileProgramFromString(vertShaderString, fragShaderString);
}

void FR::ShaderProgram::compileDefaultProgram() {
	compileProgramFromString(defaultVertShaderString, defaultFragShaderString);
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

void ShaderProgram::compileShaderFromString(std::string shaderText, GLuint shaderID) {
	
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

		std::printf("||| Compilation of shader failed, error log:\n%s\n", &(errorLog[0]));
	}
}

void FR::ShaderProgram::compileProgramFromString(std::string vertShaderText, std::string fragShaderText) {
	_programID = glCreateProgram();

	_vertShaderID = glCreateShader(GL_VERTEX_SHADER);
	_fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	compileShaderFromString(vertShaderText, _vertShaderID);
	compileShaderFromString(fragShaderText, _fragShaderID);

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