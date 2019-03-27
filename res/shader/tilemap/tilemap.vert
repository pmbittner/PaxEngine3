#version 400 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texCoords;
layout(location = 2) in int tileSetIndexIn;

out vec2 fragTextureCoords;
flat out int tileSetIndex;

uniform mat4 projection;
uniform mat4 modelview;

void main(void) {
    fragTextureCoords = texCoords;
    tileSetIndex = tileSetIndexIn;
    gl_Position = projection * modelview * vec4(position, 0.0, 1.0);
}