#include "Camera2D.h"

#include <glm\gtx\rotate_vector.hpp>

#include <iostream>

using namespace FR;


Camera2D::Camera2D() :
	_cameraPosition(glm::vec3(0.0, 0.0, 1.0)),
	_cameraFront(glm::vec3(0.0, 0.0, -1.0)),
	_cameraUp(glm::vec3(0.0, 1.0, 0.0))
{
}


Camera2D::~Camera2D() {
}

void FR::Camera2D::attach(ShaderProgram* shader) {
	_shader = shader;

	_shader->use();
	glm::mat4 projectionMatrix = glm::ortho(-_cameraSize.x / 2, _cameraSize.x / 2, -_cameraSize.y / 2, _cameraSize.y / 2);
	_shader->setUniformMat4("projection", projectionMatrix);

	update();
}

void FR::Camera2D::update() {
	updateViewMatrix();

	_shader->use();
	_shader->setUniformMat4("view", _view);
}

void FR::Camera2D::moveCam(glm::vec2 offset) {
	_cameraPosition.x += offset.x;
	_cameraPosition.y += offset.y;

	_needsViewMatrixUpdate = true;
}

void FR::Camera2D::setCamSize(glm::vec2 newSize) {
	_cameraSize = newSize;
	if (_shader != nullptr) {
		_shader->use();
		glm::mat4 projectionMatrix = glm::ortho(-_cameraSize.x / 2.0, _cameraSize.x / 2.0, -_cameraSize.y / 2.0, _cameraSize.y / 2.0);
		_shader->setUniformMat4("projection", projectionMatrix);
	}
	update();
}

glm::vec2 FR::Camera2D::getCamSize() {
	return _cameraSize;
}

void FR::Camera2D::setCamPos(glm::vec2 newPos) {
	_cameraPosition.x = newPos.x;
	_cameraPosition.y = newPos.y;

	_needsViewMatrixUpdate = true;

}

glm::vec2 FR::Camera2D::getCamPos() {
	return glm::vec2(_cameraPosition.x, _cameraPosition.y);
}

void FR::Camera2D::rotate(double rotation) {
	_cameraRotation += rotation;

	_needsCamRotUpdate = true;
}

void FR::Camera2D::setCamRot(double newRot) {
	_cameraRotation = newRot;
	
	_needsCamRotUpdate = true;
}

double FR::Camera2D::getCamRot() {
	return _cameraRotation;
}

void Camera2D::updateViewMatrix() {
	if (_needsCamRotUpdate) {
		_cameraUp = glm::rotate(glm::vec3(0.0, 1.0, 0.0), (float)_cameraRotation, _cameraFront);
		_view = glm::lookAt(_cameraPosition, _cameraPosition + _cameraFront, _cameraUp);
		_needsCamRotUpdate = false;
	}
	if (_needsViewMatrixUpdate) {
		_view = glm::lookAt(_cameraPosition, _cameraPosition + _cameraFront, _cameraUp);
		_needsViewMatrixUpdate = false;
	}
}
