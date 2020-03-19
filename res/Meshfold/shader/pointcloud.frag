#version 400 core

in vec2 fragTextureCoords;
out vec4 outColor;

uniform sampler2D textureSampler;

void main(void) {
	outColor = texture(textureSampler, fragTextureCoords);
	//outColor = vec4(1, 0, 0, 1);
}