//
// Created by Paul on 13.10.2017.
//

#include <paxcore/rendering/data/Texture.h>
#include <paxutil/log/Errors.h>

namespace PAX {
    Texture::~Texture() = default;

    int Texture::getWidth() {
        return width;
    }

    int Texture::getHeight() {
        return height;
    }

    glm::ivec2 Texture::getSize() {
        return {width, height};
    }

    Texture::WrapMode Texture::getWrapModeHorizontal() {
        return wrapHorizontal;
    }

    Texture::WrapMode Texture::getWrapModeVertical() {
        return wrapVertical;
    }

    Texture::FilterMode Texture::getFilterMode() {
        return filterMode;
    }

    void Texture::setWrapMode(PAX::Texture::WrapMode horizontal, PAX::Texture::WrapMode vertical) {
        wrapHorizontal = horizontal;
        wrapVertical   = vertical;
    }

    void Texture::setFilterMode(PAX::Texture::FilterMode mode) {
        filterMode = mode;
    }

    void Texture::setPixels(void *data, PAX::Texture::PixelFormat dataPixelFormat) {
        PAX_NOT_IMPLEMENTED();
    }
}