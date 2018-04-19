#version 400 core

layout(location = 0) in vec3 position;

uniform mat4 projection;
uniform mat4 modelview;

out float height;

void main(void) {
    height = position.y;
    gl_Position = projection * modelview * vec4(position, 1.0);
}