//
// Created by Paul on 02.07.2017.
//

#ifndef PAXENGINE3_RENDERFACTORY_H
#define PAXENGINE3_RENDERFACTORY_H

#include <core/world/scenegraph/WorldLayerSceneGraph.h>

namespace PAX {
    class SceneGraphGenerator;
    class WorldLayer;

    class RenderFactory {
    public:
        virtual WorldLayerSceneGraph* createSceneGraphNodeFor(WorldLayer *worldLayer, float z) = 0;
        virtual SceneGraphGenerator* createDefaultSceneGraphGenerator() = 0;
    };
}

#endif //PAXENGINE3_RENDERFACTORY_H
