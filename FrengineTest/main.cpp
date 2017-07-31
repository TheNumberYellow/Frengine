#include <Frengine\Window.h>
#include <Frengine\ResourceManager.h>

#include <string>
#include <vector>

#include <GL\glew.h>
#include <SDL2\SDL.h>

int main(int argc, char** argv) {

	FR::Window window;
	
	window.create("TestFrengine", 800, 600, NULL);

	FR::ResourceManager::loadTexture("Images/testImage0.png", "testImage0");
	FR::ResourceManager::loadTexture("Images/testImage1.png", "testImage1");
	FR::ResourceManager::loadTexture("Images/testImage2.png", "testImage2");
	
	
	GLfloat vertices[] = {
	   -1.0, -1.0,  0.0, 0.0, 0.0,
		0.0,  1.0,	0.0,  0.5,  1.0,
		1.0, -1.0,	0.0,  1.0, 0.0
	};

	const char* vertShader =
		"#version 450\n"
		"layout(location = 0) in vec3 vertexPosition;\n"
		"layout(location = 1) in vec2 vertexUV;\n"
		"out vec2 fragmentUV;\n"
		"void main(){\n"
		"	fragmentUV = vertexUV;\n"
		"	gl_Position = vec4(vertexPosition, 1.0);\n"
		"}\0";

	const char* fragShader =
		"#version 450\n"
		"in vec2 fragmentUV;\n"
		"out vec4 fragColour;\n"
		"uniform sampler2D sampler;\n"
		"void main(){\n"
		"	fragColour = texture(sampler, fragmentUV);\n"
		"}\0";

	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertShader, NULL);
	glCompileShader(vertexShader);


	GLint success = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE) {
		GLint maxLength = 0;

		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &errorLog[0]);

		//Exit with failure
		glDeleteShader(vertexShader); //Don't leak the shader

		std::printf("%s\n", &errorLog[0]);
	}

	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragShader, NULL);
	glCompileShader(fragmentShader);

	success = 0;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE) {
		GLint maxLength = 0;

		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &errorLog[0]);

		//Exit with failure
		glDeleteShader(fragmentShader); //Don't leak the shader

		std::printf("%s\n", &errorLog[0]);
	}

	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glUseProgram(shaderProgram);
	
	GLuint posAttrib = glGetAttribLocation(shaderProgram, "vertexPosition");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
	
	GLuint texAttrib = glGetAttribLocation(shaderProgram, "vertexUV");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	

	FR::Texture2D* texture0 = FR::ResourceManager::getTexture("testImage2");

	texture0->bind();

	FR::Texture2D* texture1 = FR::ResourceManager::getTexture("testImage0");

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	while (true) {
		
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		
		window.clear(GL_COLOR_BUFFER_BIT);
		// DRAW
		texture1->bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);

		texture0->bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// END DRAW
		window.swapBuffer();
	}

	return 0;
}