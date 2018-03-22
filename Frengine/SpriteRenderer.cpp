#include "SpriteRenderer.h"

#include <glm\gtc\matrix_transform.hpp>

using namespace FR;

SpriteRenderer::SpriteRenderer(ShaderProgram* shader) {
	_shader = shader;
	this->initRenderData();
}


SpriteRenderer::~SpriteRenderer() {
	glDeleteVertexArrays(1, &this->_quadVAO);
}

void FR::SpriteRenderer::DrawSprite(Texture2D * texture, glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec3 colour) {
	this->_shader->use();

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(position, 0.0f));

	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
	model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

	model = glm::scale(model, glm::vec3(size, 1.0f));

	this->_shader->setUniformMat4("model", model);

	glActiveTexture(GL_TEXTURE0);
	texture->bind();

	glBindVertexArray(this->_quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

}

void FR::SpriteRenderer::initRenderData() {
	GLuint VBO, EBO;
	GLfloat vertices[] = {
		// Positions			// Tex Coords
		0.0f,	0.0f,	0.0f,	0.0f,	0.0f,
		1.0f,	0.0f,	0.0f,	1.0f,	0.0f,
		1.0f,	1.0f,	0.0f,	1.0f,	1.0f,
		0.0f,	1.0f,	0.0f,	0.0f,	1.0f

	};

	GLuint elements[] = {
		0, 1, 2,
		2, 3, 0
	};

	// Generate all vertex array + buffers
	glGenVertexArrays(1, &this->_quadVAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Copy vertex data to vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Copy element array to element buffer object
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);


	// Set up vertex attribute pointers
	glBindVertexArray(this->_quadVAO);
	
	// Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);

	// Texture Coordinates
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

	// Unbind everything
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
