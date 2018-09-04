#version 400 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;

out vec2 fragTextureCoords;

uniform mat4 projection;
uniform mat4 modelview;


void main(void) {
    fragTextureCoords = uv;
    gl_Position = projection * modelview * vec4(position, 1.0);
}