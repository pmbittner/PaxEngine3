//
// Created by Bittner on 08.04.2019.
//

#include <paxcore/rendering/renderpass/RenderPassChannel.h>
#include <cassert>

namespace PAX {
    RenderPassChannel::RenderPassChannel(Texture::PixelFormat format) {

    }

    RenderPassChannel::~RenderPassChannel() = default;

    Texture * RenderPassChannel::getTexture() const {
        return texture;
    }
}