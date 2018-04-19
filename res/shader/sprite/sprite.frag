#version 400 core

in vec2 fragTextureCoords;
out vec4 outColor;

uniform sampler2D textureSampler;

void main(void) {
	//out_Color = vec4(fragTextureCoords, 1.0, 1.0);//texture(textureSampler, fragTextureCoords);
#ifdef FICK_DICH_WEG_DU_HOMOFUERST
    outColor = vec4(0, 1, 0, 1);
#else
	outColor = texture(textureSampler, fragTextureCoords);
#endif
}