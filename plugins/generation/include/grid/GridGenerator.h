//
// Created by bittner on 11/20/17.
//

#ifndef PAXENGINE3_GRIDGENERATOR_H
#define PAXENGINE3_GRIDGENERATOR_H

#include <core/rendering/data/CPUMesh.h>
#include "Grid.h"

namespace PAX {
    class GridGenerator {
    public:
        Grid generateGrid(float width, float depth, int subdivsX, int subdivsY);
    };
}

#endif //PAXENGINE3_GRIDGENERATOR_H
