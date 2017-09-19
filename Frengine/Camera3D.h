#pragma once
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ShaderProgram.h"

namespace FR {
	class Camera3D {
	public:
		Camera3D();
		~Camera3D();

		void attach(ShaderProgram* shader);
		void update();

		void setCamPos(glm::vec3 newPos);
		glm::vec3 getCamPos();

		void setCamFront(glm::vec3 newFront);
		glm::vec3 getCamFront();

		void setCamUp(glm::vec3 newUp);
		glm::vec3 getCamUp();

	private:
		ShaderProgram* _shader;

		GLfloat _yaw;
		GLfloat _pitch;

		glm::vec3 _cameraPosition;
		glm::vec3 _cameraFront;
		glm::vec3 _cameraUp;

		glm::mat4 _view;

		void updateViewMatrix();
	};
}