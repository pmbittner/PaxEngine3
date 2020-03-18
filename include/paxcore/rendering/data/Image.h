//
// Created by Paul Bittner on 18.03.2020.
//

#ifndef PAXENGINE3_IMAGE_H
#define PAXENGINE3_IMAGE_H

#include <paxutil/lib/GlmIncludes.h>
#include "Texture.h"

namespace PAX {
    class Image : public Texture {
        // RGBA
        glm::cvec4 * pixels = nullptr;

        void reallocatePixelBuffer();

    public:
        Image(int width, int height);
        ~Image() override;

        void setPixels(void * data, PixelFormat dataPixelFormat) override;
        PAX_NODISCARD const glm::cvec4* getPixels() const;

        void bind() override;
        void unbind() override;

        PAX_NODISCARD std::shared_ptr<Texture> toGPUTexture() const;
    };
}

#endif //PAXENGINE3_IMAGE_H
