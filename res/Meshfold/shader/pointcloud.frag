#version 400 core

in vec4 pointColour;
out vec4 outColor;

void main(void) {
	outColor = pointColour;
}