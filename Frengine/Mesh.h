#pragma once
#include "Drawable.h"

namespace FR {

	class Mesh : public Drawable {
	public:
		Mesh();
		~Mesh();

		void create(std::vector<GLfloat> vertices, std::vector<GLuint> elements, glm::vec3 position, glm::vec3 size, GLfloat rotationX, GLfloat rotationY, GLfloat rotationZ, Texture2D* texture);

		GLfloat getRotZ();
	};
}
