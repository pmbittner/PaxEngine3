#version 400 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoords;

out vec2 fragTextureCoords;

uniform mat4 projection;
uniform mat4 modelview;

uniform ivec2 spriteResolution;

#ifdef SPRITE_SHEET
struct SpriteSheet {
    ivec2 offset;
    ivec2 size;
};

uniform SpriteSheet spriteSheet;
#endif

void main(void) {
    /*
    vec2 halfPixelSize = 0.5f / spriteResolution;
    vec2 clampedTexCoords = clamp(texCoords, halfPixelSize, 1.0f-halfPixelSize);
    /*/
    vec2 clampedTexCoords = texCoords;
    //*/

#ifdef SPRITE_SHEET
    fragTextureCoords = (spriteSheet.offset + clampedTexCoords) / spriteSheet.size;
#else
    fragTextureCoords = clampedTexCoords;
#endif

    gl_Position = projection * modelview * vec4(position, 1.0);
}