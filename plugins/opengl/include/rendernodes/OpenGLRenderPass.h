//
// Created by Paul on 17.06.2017.
//

#ifndef PAXENGINE3_OPENGLRENDERPASS_H
#define PAXENGINE3_OPENGLRENDERPASS_H

#include <core/rendering/scenegraph/SceneGraph.h>

namespace PAX {
    namespace OpenGL{
            class OpenGLRenderPass : public SceneGraph {
            public:
                OpenGLRenderPass();
                void initialize();
                virtual void render(RenderOptions &renderOptions) override;
            };
    }
}

#endif //PAXENGINE3_OPENGLRENDERPASS_H
