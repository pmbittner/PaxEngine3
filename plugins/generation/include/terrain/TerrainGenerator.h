//
// Created by bittner on 11/20/17.
//

#ifndef PAXENGINE3_TERRAINGENERATOR_H
#define PAXENGINE3_TERRAINGENERATOR_H

#include "../grid/Grid.h"
#include "Terrain.h"

namespace PAX {
    class TerrainGenerator {
        void randomizeHeights(Grid& grid);

    public:
        Terrain* generateTerrain();
    };
}

#endif //PAXENGINE3_TERRAINGENERATOR_H
