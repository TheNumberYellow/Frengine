#version 400

in vec2 fragmentUV;
out vec4 fragColour;
uniform sampler2D sampler;

void main(){
	vec4 colour = texture(sampler, fragmentUV);
	//vec3 lum = vec3(0.299, 0.587, 0.114);
	//colour = vec4(vec3(dot(colour.rgb, lum)), colour.a);
	
	fragColour = colour;
}