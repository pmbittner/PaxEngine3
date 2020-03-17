//
// Created by paul on 07.01.19.
//

#ifndef PAXENGINE3_WORLDSCENEGRAPHFACTORY_H
#define PAXENGINE3_WORLDSCENEGRAPHFACTORY_H

#include "WorldSceneGraph.h"

namespace PAX {
    class WorldSceneGraphFactory {
    public:
        virtual WorldSceneGraph * create(World *world) = 0;
    };
}
#endif //PAXENGINE3_WORLDSCENEGRAPHFACTORY_H
