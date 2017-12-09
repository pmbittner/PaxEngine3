//
// Created by Paul on 07.12.2017.
//

#ifndef PAXENGINE3_GRID_H
#define PAXENGINE3_GRID_H

#include <core/rendering/data/CPUMesh.h>

namespace PAX {
    struct Grid : public CPUMesh {
        float width = 0;
        float depth = 0;

        int subdivsX = 0, subdivsZ = 0;

        Grid(std::vector<glm::vec3> &vertices, std::vector<glm::ivec3> faces, float width, float depth, int subdivsX, int subdivsZ) : CPUMesh(vertices, faces), width(width), depth(depth), subdivsX(subdivsX), subdivsZ(subdivsZ) {
        }

        glm::vec3& getVertexAt(int x, int z) {
            assert(0 <= x && x < subdivsX);
            assert(0 <= z && z < subdivsZ);
            
            return vertices[z + x*subdivsZ];
        }
    };
}

#endif //PAXENGINE3_GRID_H
