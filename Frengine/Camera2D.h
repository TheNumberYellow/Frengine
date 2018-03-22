#pragma once
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ShaderProgram.h"

namespace FR {
	class Camera2D {
	public:
		Camera2D();
		~Camera2D();

		void attach(ShaderProgram* shader);
		void update();

		void setCamSize(glm::vec2 newSize);

		void setCamPos(glm::vec2 newPos);
		glm::vec2 getCamPos();

		void setCamRot(double newRot);
		double getCamRot();

	private:
		ShaderProgram* _shader = nullptr;

		bool _needsViewMatrixUpdate = true;
		bool _needsCamRotUpdate = true;

		glm::vec2 _cameraSize;

		glm::vec3 _cameraPosition;
		glm::vec3 _cameraFront;
		glm::vec3 _cameraUp;
		
		double _cameraRotation;

		glm::mat4 _view;

		void updateViewMatrix();
	};
}
