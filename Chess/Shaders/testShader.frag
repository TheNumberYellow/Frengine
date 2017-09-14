#version 400

in vec2 fragmentUV;
out vec4 fragColour;
uniform sampler2D sampler;

void main(){
	fragColour = texture(sampler, fragmentUV);
}