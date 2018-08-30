//
// Created by Paul on 06.01.2018.
//

#include <core/rendering/data/SpriteSheet.h>

namespace PAX {
    SpriteSheet::SpriteSheet(int textureCount) : _textures(textureCount) {

    }

    int SpriteSheet::getTextureCount() {
        return _textures.size();
    }

    Texture* SpriteSheet::getTextureAt(int index) {
        return _textures[index];
    }
}