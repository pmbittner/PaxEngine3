#version 400 core

in vec2 fragTextureCoords;
out vec4 outColor;

uniform sampler2D textureSampler;

void main(void) {
    outColor = vec4(0, 1, 0, 1);
	//outColor = texture(textureSampler, fragTextureCoords);
}