#version 400 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texCoords;

out vec2 fragTextureCoords;

uniform mat4 projection;
uniform mat4 modelview;

uniform ivec2 spriteResolution;

void main(void) {
    fragTextureCoords = texCoords;
    gl_Position =
        projection *
        modelview *
        vec4(position, 0.0, 1.0);
}