//
// Created by Bittner on 08.04.2019.
//

#ifndef PAXENGINE3_OPENGLRENDERPASS_H
#define PAXENGINE3_OPENGLRENDERPASS_H

#include <paxcore/rendering/renderpass/RenderPass.h>
#include "OpenGLRenderPassChannel.h"

namespace PAX {
    namespace OpenGL {
        class OpenGLRenderPass : public RenderPass {
            std::vector<std::unique_ptr<OpenGLRenderPassChannel>> channels;

        public:
            OpenGLRenderPass();
            ~OpenGLRenderPass() override;

            void bind() override;
            void unbind() override;

            //const std::unique_ptr<OpenGLRenderPassChannel> & addChannel(RenderPassChannel::Format format, RenderPassChannel::ValueType valueType) override;
            //const std::unique_ptr<OpenGLRenderPassChannel> & getChannel(int id) const override;
        };
    }
}

#endif //PAXENGINE3_OPENGLRENDERPASS_H
