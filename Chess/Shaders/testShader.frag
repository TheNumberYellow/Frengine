#version 400

in vec2 fragmentUV;
out vec4 fragColour;
uniform sampler2D sampler;

void main(){
	vec4 texel = texture(sampler, fragmentUV);
	if (texel.a < 0.5)
		discard;
	//fragColour = texture(sampler, fragmentUV);
	fragColour = texel;
}