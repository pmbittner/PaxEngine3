#version 400 core

in vec2 fragTextureCoords;
out vec4 out_Color;

uniform sampler2D textureSampler;

void main(void) {
    vec2 uv = fragTextureCoords;
    out_Color = texture(textureSampler, uv);
//    out_Color = vec4(0, 1, 0, 1);
//    out_Color = vec4(fragTextureCoords, 0, 1);
}