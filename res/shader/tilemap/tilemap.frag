#version 400 core

#define NUM_MAX_TILESETS 16

in vec2 fragTextureCoords;
flat in int tileSetIndex;
out vec4 outColor;

uniform sampler2D tileSets[NUM_MAX_TILESETS];

void main(void) {
	if (tileSetIndex >= 0) {
		outColor = texture(tileSets[tileSetIndex], fragTextureCoords);
	} else {
		outColor = vec4(0, 0, 0, 0);
	}
}