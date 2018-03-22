#include "Drawable.h"

#include <glm\gtc\matrix_transform.hpp>
#include <iostream>

using namespace FR;


Drawable::Drawable() {
}


Drawable::~Drawable() {
}

void Drawable::draw(ShaderProgram* shader) {
	shader->use();

	_texture->bind();

	updateModelMatrix();
	shader->setUniformMat4("model", _modelMatrix);

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
	_needsModelMatrixUpdate = true;
}

void FR::Drawable::setRot(GLfloat newRot) {
	//_rotation = newRot;
	_rotationZ = newRot;
	_needsModelMatrixUpdate = true;
}

void FR::Drawable::updateModelMatrix() {
	if (!_needsModelMatrixUpdate)
		return;

	glm::mat4 translation = glm::translate(glm::mat4(), _position);
	glm::mat4 scale = glm::scale(glm::mat4(), _scale);
	glm::mat4 rotation;


	switch (_rotateMode) {
	case BOTTOM_LEFT:

		rotation = glm::rotate(glm::mat4(), _rotationX, glm::vec3(1.0, 0.0, 0.0));
		rotation = glm::rotate(rotation, _rotationY, glm::vec3(0.0, 1.0, 0.0));
		rotation = glm::rotate(rotation, _rotationZ, glm::vec3(1.0, 0.0, 1.0));
		break;
	case CENTER:
		glm::mat4 halfTranslation = glm::translate(glm::mat4(), glm::vec3(0.5, 0.5, 0.5));

		rotation = glm::rotate(halfTranslation, _rotationX, glm::vec3(1.0, 0.0, 0.0));
		rotation = glm::rotate(rotation, _rotationY, glm::vec3(0.0, 1.0, 0.0));
		rotation = glm::rotate(rotation, _rotationZ, glm::vec3(0.0, 0.0, 1.0));

		rotation = glm::translate(rotation, glm::vec3(-0.5, -0.5, -0.5));
		break;
	}

	// TODO:	Right now rotation around center only works when size of actual (non-scaled) vertices is 1
	//			This works for 2D sprites since they all have a size of 1 but may not work with 3D meshes
	_modelMatrix = translation * scale * rotation;

	_needsModelMatrixUpdate = false;
}
