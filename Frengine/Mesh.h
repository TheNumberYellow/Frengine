#pragma once
#include "Drawable.h"

namespace FR {

	class Mesh : public Drawable {
	public:
		Mesh();
		~Mesh();

		void create(VerticesInfo& vInfo, GLuint numVertices, GLuint numElements, glm::vec3 position, glm::vec3 size, GLfloat rotationX, GLfloat rotationY, GLfloat rotationZ, Texture2D* texture);

	};
}
