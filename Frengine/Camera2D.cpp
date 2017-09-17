#include "Camera2D.h"

using namespace FR;


Camera2D::Camera2D() :
	_cameraPosition(glm::vec3(0.0, 0.0, 3.0)),
	_cameraFront(glm::vec3(0.0, 0.0, -1.0)),
	_cameraUp(glm::vec3(0.0, 1.0, 0.0))
{

}


Camera2D::~Camera2D() {
}

void FR::Camera2D::attach(ShaderProgram* shader) {
	_shader = shader;

	update();
}

void FR::Camera2D::update() {


	updateViewMatrix();

	_shader->use();
	_shader->setUniformMat4("view", _view);
}

void Camera2D::updateViewMatrix() {
	_view = glm::lookAt(_cameraPosition, _cameraPosition + _cameraFront, _cameraUp);
}
