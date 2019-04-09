//
// Created by Bittner on 08.04.2019.
//

#include <paxopengl/rendernodes/OpenGLRenderPass.h>

namespace PAX {
    namespace OpenGL {
        OpenGLRenderPass::OpenGLRenderPass() : RenderPass() {}
        OpenGLRenderPass::~OpenGLRenderPass() = default;

        void OpenGLRenderPass::bind() {

        }

        void OpenGLRenderPass::unbind() {

        }

        const std::unique_ptr<OpenGLRenderPassChannel> & OpenGLRenderPass::addChannel(PAX::RenderPassChannel::Format format,
                                          PAX::RenderPassChannel::ValueType valueType) {
            channels.emplace_back(std::move(std::make_unique<OpenGLRenderPassChannel>(format, valueType)));
            channels.back()->attached(this);
            return channels.back();
        }

        const std::unique_ptr<RenderPassChannel>& OpenGLRenderPass::getChannel(int id) const {
            return channels.at(id); //?
        }
    }
}