//
// Created by Bittner on 08.04.2019.
//

#ifndef PAXENGINE3_RENDERPASSCHANNEL_H
#define PAXENGINE3_RENDERPASSCHANNEL_H

#include <paxcore/rendering/data/Texture.h>

namespace PAX {
    class RenderPassChannel {
    private:
        Texture * texture;

    public:
        RenderPassChannel(Texture::PixelFormat format);
        ~RenderPassChannel();

        Texture * getTexture() const;
    };
}

#endif //PAXENGINE3_RENDERPASSCHANNEL_H
