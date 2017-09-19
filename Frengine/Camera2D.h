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

		void setCamPos(glm::vec2 newPos);
		glm::vec2 getCamPos();

	private:
		ShaderProgram* _shader;

		glm::vec3 _cameraPosition;
		glm::vec3 _cameraFront;
		glm::vec3 _cameraUp;

		glm::mat4 _view;

		void updateViewMatrix();
	};
}
