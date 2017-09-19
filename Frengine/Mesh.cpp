#include "Mesh.h"

using namespace FR;


Mesh::Mesh() {
}


Mesh::~Mesh() {
}

void FR::Mesh::create(VerticesInfo& vInfo, GLuint numVertices, GLuint numElements, glm::vec3 position, glm::vec3 size, GLfloat rotationX, GLfloat rotationY, GLfloat rotationZ, Texture2D* texture) {
	for (int i = 0; i < numVertices; i++) {
		printf("VertexArray [%d]: %f\n", i, vInfo.vertices[i]);
	}
	for (int i = 0; i < numElements; i++) {
		printf("ElementArray [%d]: %d\n", i, vInfo.elements[i]);
	}
	
	_position = position;

	_rotationX = rotationX;
	_rotationY = rotationY;
	_rotationZ = rotationZ;

	_scale = size;

	_rotateMode = CENTER;

	// Create + Bind vertex array object
	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);

	// Create + Bind vertex buffer object
	glGenBuffers(1, &_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);

	_numVertices = numElements;

	// Copy vertices to buffer object
	glBufferData(GL_ARRAY_BUFFER, numVertices, (void*)vInfo.vertices, GL_STATIC_DRAW);


	// Create + Bind element array
	glGenBuffers(1, &_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);

	// Copy elements to buffer object
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numElements, (void*)vInfo.elements, GL_STATIC_DRAW);

	// Set up vertex attribute pointers
	// Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);

	// Texture Coordinates
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

	// Assign texture
	_texture = texture;

	// Assign drawmode
	_drawMode = FR_TRIANGLES;

	// Unbind everything
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
