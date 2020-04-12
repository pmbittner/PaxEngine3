//
// Created by Paul Bittner on 12.04.2020.
//

#ifndef PAXENGINE3_OPENGLRENDERPASSFACTORY_H
#define PAXENGINE3_OPENGLRENDERPASSFACTORY_H

#include <paxcore/rendering/renderpass/RenderPassFactory.h>
#include "../rendernodes/OpenGLRenderPass.h"

namespace PAX {
    namespace OpenGL {
        class OpenGLRenderPassFactory : public RenderPassFactory {
        public:
            PAX_NODISCARD OpenGLRenderPass * create(const glm::ivec2 &resolution) override;
        };
    }
}

#endif //PAXENGINE3_OPENGLRENDERPASSFACTORY_H
