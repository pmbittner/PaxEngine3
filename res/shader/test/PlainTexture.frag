#version 400 core

in vec2 fragTextureCoords;
out vec4 out_Color;

uniform sampler2D textureSampler;

void main(void) {
	out_Color = texture(textureSampler, fragTextureCoords);
	//out_Color = vec4(fragTextureCoords, 0, 1);
}