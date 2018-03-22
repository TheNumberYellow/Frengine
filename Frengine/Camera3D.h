#pragma once
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ShaderProgram.h"

namespace FR {
	enum Camera_Movement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};
}

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

		void processMouseMovement(GLfloat xMove, GLfloat yMove);
		void processKeyboard(Camera_Movement direction, GLfloat deltaTime);

	private:
		ShaderProgram* _shader;

		glm::vec3 _cameraPosition;
		glm::vec3 _cameraFront;
		glm::vec3 _cameraUp;
		glm::vec3 _cameraRight;
		glm::vec3 _worldUp;

		glm::mat4 _view;

		GLfloat _yaw;
		GLfloat _pitch;

		GLfloat _movementSpeed;
		GLfloat _mouseSensitivity;
		GLfloat _fov;

		void updateCameraVectors();
		void updateViewMatrix();
	};
}