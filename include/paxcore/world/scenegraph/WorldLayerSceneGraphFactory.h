//
// Created by paul on 07.01.19.
//

#ifndef PAXENGINE3_WORLDLAYERSCENEGRAPHFACTORY_H
#define PAXENGINE3_WORLDLAYERSCENEGRAPHFACTORY_H

#include "WorldLayerSceneGraph.h"

namespace PAX {
    class WorldLayerSceneGraphFactory {
    public:
        virtual std::shared_ptr<WorldLayerSceneGraph> create(WorldLayer *worldLayer, float z) = 0;
    };
}
#endif //PAXENGINE3_WORLDLAYERSCENEGRAPHFACTORY_H
