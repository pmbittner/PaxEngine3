//
// Created by Paul on 02.07.2017.
//

#ifndef PAXENGINE3_OPENGLWORLDLAYERRENDERPASS_H
#define PAXENGINE3_OPENGLWORLDLAYERRENDERPASS_H

#include "../../core/rendering/scenegraph/SceneGraph.h"

namespace PAX {
    namespace OpenGL{
        class OpenGLWorldLayerRenderPass : public SceneGraph {
        public:
            OpenGLWorldLayerRenderPass();
            virtual void render(RenderOptions &renderOptions) override;
        };
    }
}

#endif //PAXENGINE3_OPENGLWORLDLAYERRENDERPASS_H
