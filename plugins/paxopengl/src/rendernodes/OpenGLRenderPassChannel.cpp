//
// Created by Bittner on 08.04.2019.
//

#include <paxopengl/rendernodes/OpenGLRenderPassChannel.h>

namespace PAX {
    namespace OpenGL {
        OpenGLRenderPassChannel::OpenGLRenderPassChannel(PAX::RenderPassChannel::Format format,
                                                         PAX::RenderPassChannel::ValueType valueType)
        : RenderPassChannel(format, valueType),
        texture()
        {

        }

        OpenGLRenderPassChannel::~OpenGLRenderPassChannel() = default;

        const OpenGLTexture2D& OpenGLRenderPassChannel::getTexture() const {
            return texture;
        }
    }
}