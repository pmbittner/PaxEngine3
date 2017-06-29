//
// Created by Paul on 30.06.2017.
//

#ifndef PAXENGINE3_SPRITE_H
#define PAXENGINE3_SPRITE_H

#include "Graphics.h"
#include "resource/Texture.h"

namespace PAX {
    class Sprite : public Graphics {
        Texture *_texture;

    public:
        Sprite(Texture *texture){}
    };
}

#endif //PAXENGINE3_SPRITE_H
