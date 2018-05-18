#include "Sprite.h"
using namespace FR;

GLuint Sprite::_staticVAO;
bool Sprite::_isVAOInitialized = false;

Sprite::Sprite() {
}

FR::Sprite::Sprite(glm::vec2 position, glm::vec2 size, GLfloat rotation, Texture2D* texture) {
	/// TODO: Not sure if there isn't a better way to do this
	if (!_isVAOInitialized) {
		Sprite::initRenderData();
		_isVAOInitialized = true;
	}
	this->create(position, size, rotation, texture);
}


Sprite::~Sprite() {
}

void FR::Sprite::create(glm::vec2 position, glm::vec2 size, GLfloat rotation, Texture2D* texture) {
	_position = glm::vec3(position.x, position.y, 0);
	
	_rotationX = 0;
	_rotationY = 0;
	_rotationZ = rotation;
	_scale = glm::vec3(size.x, size.y, 1.0);

	_rotateMode = CENTER;
	_numVertices = 6;

	// Assign texture
	_texture = texture;

	// Assign drawmode
	_drawMode = FR_TRIANGLES;

	_VAO = _staticVAO;
}

void FR::Sprite::setPos(glm::vec2 newPos) {
	glm::vec3 newPos3x3{ newPos.x, newPos.y, 0 };

	_position = newPos3x3;

	_needsModelMatrixUpdate = true;
}

glm::vec2 FR::Sprite::getPos() {
	return glm::vec2(_position.x, _position.y);
}

void FR::Sprite::move(glm::vec2 movement)
{
	glm::vec3 newPos3x3{ movement.x, movement.y, 0 };

	_position += newPos3x3;

	_needsModelMatrixUpdate = true;
}

void FR::Sprite::setRot(GLfloat newRot) {
	_rotationZ = newRot;

	_needsModelMatrixUpdate = true;
}

void FR::Sprite::rotate(GLfloat rotation) {
	_rotationZ += rotation;

	_needsModelMatrixUpdate = true;
}

GLfloat FR::Sprite::getRot() {
	return _rotationZ;
}

void FR::Sprite::setScale(glm::vec2 newScale) {
	_scale = glm::vec3(newScale.x, newScale.y, 1.0);

	_needsModelMatrixUpdate = true;
}

glm::vec2 FR::Sprite::getScale() {
	return glm::vec2(_scale.x, _scale.y);
}

void FR::Sprite::initRenderData() {
	GLuint VBO, EBO;
	GLfloat vertices[] = {
		// Positions			// Tex Coords
		0.0f,	0.0f,	0.0f,	0.0f,	0.0f,
		1.0f,	0.0f,	0.0f,	1.0f,	0.0f,
		1.0f,	1.0f,	0.0f,	1.0f,	1.0f,
		0.0f,	1.0f,	0.0f,	0.0f,	1.0f

	};

	GLuint elements[] = {
		0, 1, 2,
		2, 3, 0
	};

	// Generate all vertex array + buffers

	glGenVertexArrays(1, &_staticVAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	
	glBindVertexArray(_staticVAO);

	// Copy vertex data to vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Copy element array to element buffer object
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);


	// Set up vertex attribute pointers

	// Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);

	// Texture Coordinates
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

	// Unbind everything
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
