#include "Drawable.h"

#include <glm\gtc\matrix_transform.hpp>

using namespace FR;


Drawable::Drawable() {
}


Drawable::~Drawable() {
}

void Drawable::draw(ShaderProgram* shader) {
	shader->use();
	//TODO: Apply uniforms

	_texture->bind();

	glm::mat4 transformation;
	transformation = glm::translate(transformation, _position);

	shader->setUniformMat4("transformation", transformation);

	// Determine draw mode
	GLenum glDrawMode;

	switch (_drawMode) {
	case FR_TRIANGLES:
		glDrawMode = GL_TRIANGLES;
		break;
	case FR_LINES:
		glDrawMode = GL_LINES;
		break;
	case FR_POINTS:
		glDrawMode = GL_POINTS;
		break;
	default:
		glDrawMode = GL_TRIANGLES;
		break;
	}

	// Draw elements specified in the element buffer object
	glBindVertexArray(_VAO);
	glDrawElements(glDrawMode, _numVertices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Drawable::setPos(glm::vec3 newPos) {
	_position = newPos;
}