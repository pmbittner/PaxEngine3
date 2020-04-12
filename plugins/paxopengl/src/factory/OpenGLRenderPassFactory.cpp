//
// Created by Paul Bittner on 12.04.2020.
//

#include <paxopengl/factory/OpenGLRenderPassFactory.h>

namespace PAX::OpenGL {
    OpenGLRenderPass * OpenGLRenderPassFactory::create(const glm::ivec2 &resolution) {
        return new OpenGLRenderPass(resolution);
    }
}