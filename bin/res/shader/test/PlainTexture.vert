#version 400 core

in vec3 position;
in vec2 texCoord;

out vec2 fragTextureCoords;

uniform mat4 projection;
uniform mat4 modelview;

void main(void) {
    fragTextureCoords = texCoord;
    gl_Position = projection * modelview * vec4(position, 1.0);
}