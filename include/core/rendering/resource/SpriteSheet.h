//
// Created by Paul on 06.01.2018.
//

#ifndef PAXENGINE3_SPRITESHEET_H
#define PAXENGINE3_SPRITESHEET_H

#include <vector>
#include "Texture.h"

namespace PAX {
    class SpriteSheet {
    protected:
        std::vector<Texture*> _textures;

    public:
        SpriteSheet(int textureCount);

        int getTextureCount();
        Texture* getTextureAt(int index);
    };
}

#endif //PAXENGINE3_SPRITESHEET_H
