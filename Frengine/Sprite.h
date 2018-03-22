#pragma once
#include "Drawable.h"

namespace FR {
	class Sprite : public Drawable {
	public:
		Sprite();
		Sprite(glm::vec2 position, glm::vec2 size, GLfloat rotation, Texture2D* texture);
		~Sprite();

		void create(glm::vec2 position, glm::vec2 size, GLfloat rotation, Texture2D* texture);
		void createVertices();

		void setPos(glm::vec2 newPos);
		glm::vec2 getPos();

		void setRot(GLfloat newRot);
		GLfloat getRot();

		void setScale(glm::vec2 newScale);
		glm::vec2 getScale();

	};
}
