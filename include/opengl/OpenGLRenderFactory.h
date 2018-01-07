//
// Created by Paul on 02.07.2017.
//

#ifndef PAXENGINE3_OPENGLRENDERFACTORY_H
#define PAXENGINE3_OPENGLRENDERFACTORY_H

#include <core/world/scenegraph/WorldLayerSceneGraph.h>
#include "../core/rendering/RenderFactory.h"

namespace PAX {
    namespace OpenGL {
        class OpenGLRenderFactory : public RenderFactory {
        public:
            virtual WorldLayerSceneGraph* createSceneGraphNodeFor(WorldLayer *worldLayer, float z) override;
            virtual SceneGraphGenerator* createDefaultSceneGraphGenerator() override;
        };
    }
}

#endif //PAXENGINE3_OPENGLRENDERFACTORY_H
