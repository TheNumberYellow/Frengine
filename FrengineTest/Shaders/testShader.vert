#version 400

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexUV;
out vec2 fragmentUV;

uniform mat4 projection;
uniform mat4 transformation;

void main() {
	fragmentUV = vertexUV;
	gl_Position = projection * transformation * vec4(vertexPosition, 1.0);
}