#version 400 core

in vec2 fragTextureCoords;
in float tileSetIndex;
out vec4 outColor;

uniform sampler2D tileSets[NUM_MAX_TILESETS];

void main(void) {
	if (tileSetIndex >= 0) {
		//#ifdef DISPLAY_MODE_UV
		//outColor = vec4(fragTextureCoords, 0, 1);
		//return;
		//#endif

		/*
		if (tileSetIndex > 1) {
			outColor = vec4(1, 0, 0, 1);
			return;
		}//*/

		int i = int(tileSetIndex);

		//vec2 halfPixel = 0.5 / textureSize(tileSets[i], 0);
		//vec2 insetFragTexCoords = clamp(fragTextureCoords, halfPixel, vec2(1, 1) - halfPixel);
		outColor = texture(tileSets[i], fragTextureCoords);
	} else {
		discard;
	}
}