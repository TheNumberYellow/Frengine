#include "GLTexture.h"
using namespace FR;

#include <stdio.h>

FR::Texture2D::Texture2D() :
	_width(0), _height(0),
	_internalFormat(GL_RGB),
	_imageFormat(GL_RGB),
	_textureMinFilter(GL_LINEAR),
	_textureMagFilter(GL_LINEAR)
{
	glGenTextures(1, &_id);
	printf("Texture ID: %u\n", _id);
}

FR::Texture2D::~Texture2D() {
	glDeleteTextures(1, &_id);
}

void Texture2D::generate(unsigned char* img, GLuint width, GLuint height) {
	_width = width;
	_height = height;
	
	// Bind to texture
	glBindTexture(GL_TEXTURE_2D, _id);

	// Upload image data to bound texture
	glTexImage2D(GL_TEXTURE_2D, 0, _internalFormat, _width, _height, 0, _imageFormat, GL_UNSIGNED_BYTE, img);

	// TODO: Set more texture specific parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _textureMinFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _textureMagFilter);

	// Unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);

}

const void Texture2D::bind() {
	glBindTexture(GL_TEXTURE_2D, _id);
}

void FR::Texture2D::setFormat(GLuint format) {
	_internalFormat = format;
	_imageFormat = format;
}
