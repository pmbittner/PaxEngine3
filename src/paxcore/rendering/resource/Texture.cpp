//
// Created by Paul on 13.10.2017.
//

#include <paxcore/rendering/data/Texture.h>
#include <polypropylene/log/Errors.h>

namespace PAX {
    unsigned int Texture::GetNumberOfChannels(PAX::Texture::PixelFormat pixelFormat) {
        if (pixelFormat == PixelFormat::RGB || pixelFormat == PixelFormat::BGR) {
            return 3;
        } else if (pixelFormat == PixelFormat::RGBA) {
            return 4;
        } else if (pixelFormat == PixelFormat::None) {
            return 0;
        }

        PAX_THROW_RUNTIME_ERROR("Unsupported Pixelformat: " << int(pixelFormat));
    }

    Texture::~Texture() = default;

    int Texture::getWidth() const {
        return width;
    }

    int Texture::getHeight() const {
        return height;
    }

    glm::ivec2 Texture::getSize() const {
        return {width, height};
    }

    Texture::WrapMode Texture::getWrapModeHorizontal() const {
        return wrapHorizontal;
    }

    Texture::WrapMode Texture::getWrapModeVertical() const {
        return wrapVertical;
    }

    Texture::FilterMode Texture::getFilterMode() const {
        return filterMode;
    }

    Texture::PixelFormat Texture::getPixelFormat() const {
        return pixelFormat;
    }

    Texture::ColourType Texture::getColourType() const {
        return colourType;
    }

    void Texture::setWrapMode(PAX::Texture::WrapMode horizontal, PAX::Texture::WrapMode vertical) {
        wrapHorizontal = horizontal;
        wrapVertical   = vertical;
    }

    void Texture::setFilterMode(PAX::Texture::FilterMode mode) {
        filterMode = mode;
    }
}