#include "Camera3D.h"

using namespace FR;


Camera3D::Camera3D() :
	_cameraPosition(glm::vec3(0.0, 0.0, 1.0)),
	_cameraFront(glm::vec3(0.0, 0.0, -1.0)),
	_cameraUp(glm::vec3(0.0, 1.0, 0.0)),
	_yaw(0.0f),
	_pitch(0.0f)
{
}


Camera3D::~Camera3D() {
}

void FR::Camera3D::attach(ShaderProgram* shader) {
	_shader = shader;

	update();
}

void FR::Camera3D::update() {
	updateViewMatrix();

	_shader->use();
	_shader->setUniformMat4("view", _view);
}

void FR::Camera3D::setCamPos(glm::vec3 newPos) {
	_cameraPosition = newPos;
}

glm::vec3 FR::Camera3D::getCamPos() {
	return _cameraPosition;
}

void FR::Camera3D::setCamFront(glm::vec3 newFront) {
	_cameraFront = newFront;
}

glm::vec3 FR::Camera3D::getCamFront() {
	return _cameraFront;
}

void FR::Camera3D::setCamUp(glm::vec3 newUp) {
	_cameraUp = newUp;
}

glm::vec3 FR::Camera3D::getCamUp() {
	return _cameraUp;
}

void FR::Camera3D::updateViewMatrix() {

	_view = glm::lookAt(_cameraPosition, _cameraPosition + _cameraFront, _cameraUp);
}
