//
// Created by Paul on 02.07.2017.
//

#ifndef PAXENGINE3_RENDERFACTORY_H
#define PAXENGINE3_RENDERFACTORY_H

namespace PAX {
    class SceneGraph;
    class SceneGraphGenerator;
    class WorldLayer;

    class RenderFactory {
    public:
        virtual SceneGraph* createSceneGraphNodeFor(WorldLayer *worldLayer) = 0;
        virtual SceneGraphGenerator* createSceneGraphGeneratorFor(WorldLayer *worldLayer) = 0;
    };
}

#endif //PAXENGINE3_RENDERFACTORY_H
