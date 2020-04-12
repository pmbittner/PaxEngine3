//
// Created by Bittner on 10/07/2019.
//

#ifndef PAXENGINE3_TEXTUREFACTORY_H
#define PAXENGINE3_TEXTUREFACTORY_H

#include <memory>
#include <paxcore/rendering/data/Texture.h>

namespace PAX {
    class TextureFactory {
    public:
        PAX_NODISCARD virtual std::shared_ptr<Texture> create(int width, int height) = 0;
        PAX_NODISCARD virtual std::shared_ptr<Texture> create(int width, int height, Texture::PixelFormat pixelFormat, Texture::ColourType colourType) = 0;
    };
}

#endif //PAXENGINE3_TEXTUREFACTORY_H
