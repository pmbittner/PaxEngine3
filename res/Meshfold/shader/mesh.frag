#version 400 core

in vec2 fragTextureCoords;
out vec4 out_Color;

uniform sampler2D textureSampler;

void main(void) {
    vec2 uv = fragTextureCoords;
    //uv.x = 1 - uv.x;

    uv = vec2(uv.x, 1 - uv.y);
	out_Color = texture(textureSampler, uv);
}