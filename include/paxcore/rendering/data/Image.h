//
// Created by Paul Bittner on 18.03.2020.
//

#ifndef PAXENGINE3_IMAGE_H
#define PAXENGINE3_IMAGE_H

#include "Colour.h"
#include "Texture.h"

namespace PAX {
    class Image : public Texture {
    private:
        // RGBA
        Colour * pixels = nullptr;

        void reallocatePixelBuffer();

    public:
        Image(int width, int height);
        ~Image() override;

        void setPixels(void * data, PixelFormat dataPixelFormat, ColourType colourType) override;
        void initEmptyTexture(PixelFormat dataPixelFormat, ColourType colourType) override;
        PAX_NODISCARD const Colour* getPixels() const;

        void setColorAt(const glm::ivec2 & pixel, const Colour & colour);
        void fill(const Colour & colour);
        void drawLine(const glm::vec2 & p, const glm::vec2 & q, const Colour & colour);
        void fillRect(const glm::vec2 & p, const glm::vec2 & q, const Colour & colour);

        void bind() override;
        void unbind() override;

        PAX_NODISCARD std::shared_ptr<Texture> toGPUTexture() const;
    };
}

#endif //PAXENGINE3_IMAGE_H
