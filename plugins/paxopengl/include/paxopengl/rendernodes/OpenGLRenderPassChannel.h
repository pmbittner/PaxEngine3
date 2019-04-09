//
// Created by Bittner on 08.04.2019.
//

#ifndef PAXENGINE3_OPENGLRENDERPASSCHANNEL_H
#define PAXENGINE3_OPENGLRENDERPASSCHANNEL_H

#include <paxcore/rendering/renderpass/RenderPassChannel.h>
#include <paxopengl/resource/OpenGLTexture2D.h>

namespace PAX {
    namespace OpenGL {
        class OpenGLRenderPassChannel : public RenderPassChannel {
            OpenGLTexture2D texture;

        public:
            OpenGLRenderPassChannel(Format format, ValueType valueType);
            ~OpenGLRenderPassChannel() override;

            virtual const OpenGLTexture2D &getTexture() const;
        };
    }
}

#endif //PAXENGINE3_OPENGLRENDERPASSCHANNEL_H
