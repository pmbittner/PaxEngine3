#version 400 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoords;

out vec2 fragTextureCoords;

uniform mat4 projection;
uniform mat4 modelview;

#ifdef SPRITE_SHEET
struct SpriteSheet {
    ivec2 offset;
    ivec2 size;
};

uniform SpriteSheet spriteSheet;
#endif

void main(void) {
#ifdef SPRITE_SHEET
    fragTextureCoords = (spriteSheet.offset + texCoords) / spriteSheet.size;
#else
    fragTextureCoords = texCoords;
#endif

    gl_Position = projection * modelview * vec4(position, 1.0);
}