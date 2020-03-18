#version 400 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec4 colour;

out vec4 pointColour;

uniform mat4 projection;
uniform mat4 modelview;

void main(void) {
    pointColour = colour;
    gl_Position = projection * modelview * vec4(position, 1.0, 1.0);
}