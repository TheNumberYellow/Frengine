#pragma once
#include <GL\glew.h>

namespace FR {
	class Texture2D {
	public:
		Texture2D();
		~Texture2D();

		void generate(unsigned char* img, GLuint width, GLuint height);
		const void bind();

		GLuint getID() { return _id; }

		GLuint getWidth() { return _width; }
		GLuint getHeight() { return _height; }

		void setFormat(GLenum format);

	private:
		// OpenGL handle for texture
		GLuint _id;
		// Height and width of texture
		GLuint _width, _height;

		// Format in which to save texture
		GLuint _internalFormat;
		// Format of uploaded texture data (when sent to generate)
		GLuint _imageFormat;

		// Setting of minifying and magnifying method to use (GL_NEAREST or GL_NEAREST, discounting mipmap options) 
		GLint _textureMinFilter;
		GLint _textureMagFilter;
	};

}