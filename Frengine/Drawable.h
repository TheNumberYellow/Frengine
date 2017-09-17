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
	enum RotateMode {
		BOTTOM_LEFT,
		CENTER
	};
}

namespace FR {
	class Drawable {
	public:
		Drawable();
		~Drawable();

		void draw(ShaderProgram* shader);

		void setPos(glm::vec3 newPos);
		void setRot(GLfloat newRot);

	protected:
		GLuint _VBO, _VAO, _EBO;
		unsigned int _numVertices;
		DrawMode _drawMode;
		RotateMode _rotateMode;

		glm::vec3 _position;
		glm::vec3 _scale;
		GLfloat _rotation;
		glm::vec3 _rotationVector;

		Texture2D* _texture;
	};
}
