#pragma once

#include "ShaderProgram.h"
#include "GLTexture.h"

namespace FR {
	class SpriteRenderer {
	public:
		SpriteRenderer(ShaderProgram* shader);
		~SpriteRenderer();

		void DrawSprite(Texture2D* texture, glm::vec2 position,
			glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f,
			glm::vec3 colour = glm::vec3(1.0f));

	private:
		ShaderProgram* _shader;
		GLuint _quadVAO;
		void initRenderData();
	};
}
