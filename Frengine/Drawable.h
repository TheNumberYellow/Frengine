#pragma once
#include <GL\glew.h>
#include <glm\glm.hpp>

#include "ShaderProgram.h"
#include "GLTexture.h"

namespace FR {
	enum DrawMode {
		FR_TRIANGLES,
		FR_LINES,
		FR_POINTS
	};
}

namespace FR {
	class Drawable {
	public:
		Drawable();
		~Drawable();

		void draw(ShaderProgram* shader);

		void setPos(glm::vec3 newPos);

	protected:
		GLuint _VBO, _VAO, _EBO;
		unsigned int _numVertices;
		DrawMode _drawMode;

		glm::vec3 _position;
		GLfloat _rotation;

		Texture2D* _texture;
	};
}
