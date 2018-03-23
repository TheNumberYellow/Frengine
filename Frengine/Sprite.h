#pragma once
#include "Drawable.h"

namespace FR {
	class Sprite : public Drawable {
	public:
		Sprite();
		Sprite(glm::vec2 position, glm::vec2 size, GLfloat rotation, Texture2D* texture);
		~Sprite();

		void create(glm::vec2 position, glm::vec2 size, GLfloat rotation, Texture2D* texture);

		void setPos(glm::vec2 newPos);
		glm::vec2 getPos();

		void setRot(GLfloat newRot);
		GLfloat getRot();

		void setScale(glm::vec2 newScale);
		glm::vec2 getScale();
	private:

		static void initRenderData();

		// All sprites will use same vertex array object (same simple quad)
		static GLuint _staticVAO;
		static bool _isVAOInitialized;
	};
}
