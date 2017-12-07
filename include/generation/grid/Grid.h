//
// Created by Paul on 07.12.2017.
//

#ifndef PAXENGINE3_GRID_H
#define PAXENGINE3_GRID_H

#include <core/rendering/data/CPUMesh.h>

namespace PAX {
    struct Grid : public CPUMesh {
        int width = 0;
        int depth = 0;
        
        glm::vec3& getVertexAt(int x, int z) {
            assert(0 <= x && x < width);
            assert(0 <= z && z < depth);
            
            return vertices[z + x*depth];
        }
    };
}

#endif //PAXENGINE3_GRID_H
