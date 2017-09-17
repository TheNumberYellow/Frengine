#include "Drawable.h"

#include <glm\gtc\matrix_transform.hpp>

using namespace FR;


Drawable::Drawable() {
}


Drawable::~Drawable() {
}

void Drawable::draw(ShaderProgram* shader) {
	//printf("Drawing\n");
	
	shader->use();
	//TODO: Apply uniforms

	_texture->bind();

	glm::mat4 model;
	
	glm::mat4 translation = glm::translate(glm::mat4(), _position);
	glm::mat4 scale = glm::scale(glm::mat4(), _scale);
	glm::mat4 rotation;

	//switch (_rotateMode) {
	//case BOTTOM_LEFT:
	//	rotation = glm::rotate(glm::mat4(), _rotation, _rotationVector);
	//	break;
	//case CENTER:
	//	glm::mat4 halfTranslation = glm::translate(glm::mat4(), glm::vec3(0.5, 0.5, 0.5));
	//	rotation = glm::rotate(halfTranslation, _rotation, _rotationVector);
	//	rotation = glm::translate(rotation, glm::vec3(-0.5, -0.5, -0.5));
	//	break;
	//}
	
	model = translation * scale * rotation;

	shader->setUniformMat4("model", translation);

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

void FR::Drawable::setRot(GLfloat newRot) {
	_rotation = newRot;
}
