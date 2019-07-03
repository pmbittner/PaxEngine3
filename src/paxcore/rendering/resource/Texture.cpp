//
// Created by Paul on 13.10.2017.
//

#include <paxcore/rendering/data/Texture.h>

namespace PAX {
    Texture::~Texture() = default;

    int Texture::getWidth() {
        return _width;
    }

    int Texture::getHeight() {
        return _height;
    }

    glm::ivec2 Texture::getSize() {
        return {_width, _height};
    }

    Texture::WrapMode Texture::getWrapModeHorizontal() {
        return _wrapHorizontal;
    }

    Texture::WrapMode Texture::getWrapModeVertical() {
        return _wrapVertical;
    }

    void Texture::setWrapMode(PAX::Texture::WrapMode horizontal, PAX::Texture::WrapMode vertical) {
        _wrapHorizontal = horizontal;
        _wrapVertical   = vertical;
    }
}