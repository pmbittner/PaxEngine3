//
// Created by Paul on 02.07.2017.
//

#ifndef PAXENGINE3_RENDERFACTORY_H
#define PAXENGINE3_RENDERFACTORY_H

#include <core/rendering/scenegraph/SceneGraph.h>

namespace PAX {
    class SceneGraphGenerator;
    class WorldLayer;

    class RenderFactory {
    public:
        virtual SceneGraph* createSceneGraphNodeFor(WorldLayer *worldLayer) = 0;
        virtual SceneGraphGenerator* createDefaultSceneGraphGenerator() = 0;
    };
}

#endif //PAXENGINE3_RENDERFACTORY_H
