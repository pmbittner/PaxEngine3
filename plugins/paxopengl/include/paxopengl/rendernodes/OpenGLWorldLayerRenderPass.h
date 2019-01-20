//
// Created by Paul on 02.07.2017.
//

#ifndef PAXENGINE3_OPENGLWORLDLAYERRENDERPASS_H
#define PAXENGINE3_OPENGLWORLDLAYERRENDERPASS_H

#include <paxcore/world/scenegraph/WorldLayerSceneGraph.h>

namespace PAX {
    namespace OpenGL{
        class OpenGLWorldLayerRenderPass : public WorldLayerSceneGraph {
        public:
            OpenGLWorldLayerRenderPass(float z);
            virtual void render(RenderOptions &renderOptions) override;
        };
    }
}

#endif //PAXENGINE3_OPENGLWORLDLAYERRENDERPASS_H
