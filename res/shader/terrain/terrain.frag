#version 400 core

in float height;

out vec4 out_Color;

vec4 minColor = vec4(0, 0, 1, 1);
vec4 maxColor = vec4(1, 0, 0, 1);

void main(void) {
	out_Color = mix(minColor, maxColor, height);
}