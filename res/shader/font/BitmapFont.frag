#version 400 core

in vec2 fragTextureCoords;
out vec4 out_Color;

uniform sampler2D textureSampler;
uniform float opacity;

void main(void) {
    vec2 uv = fragTextureCoords;
    vec4 color = texture(textureSampler, uv);
    color.w *= opacity;
//    color = vec4(0, 1, 0, 1);
//    color = vec4(fragTextureCoords, 0, 1);
    out_Color = color;
}