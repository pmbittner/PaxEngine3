//
// Created by Bittner on 10/07/2019.
//

#ifndef PAXENGINE3_OPENGLTEXTUREFACTORY_H
#define PAXENGINE3_OPENGLTEXTUREFACTORY_H

#include <paxcore/rendering/factory/TextureFactory.h>

namespace PAX {
    namespace OpenGL {
        class OpenGLTextureFactory : public TextureFactory {
        public:
            PAX_NODISCARD std::shared_ptr<Texture> create(int width, int height) override;
            PAX_NODISCARD std::shared_ptr<Texture> create(int width, int height, Texture::PixelFormat pixelFormat, Texture::ColourType colourType) override;
        };
    }
}

#endif //PAXENGINE3_OPENGLTEXTUREFACTORY_H
