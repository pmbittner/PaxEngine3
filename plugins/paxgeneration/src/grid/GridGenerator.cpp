//
// Created by bittner on 11/20/17.
//

#include <generation/grid/GridGenerator.h>
#include <utility/math/Conversion.h>
#include <iostream>

namespace PAX {
    Grid GridGenerator::generateGrid(float width, float depth, int subdivsX, int subdivsZ) {
        float xstep = width / subdivsX;
        float zstep = depth / subdivsZ;

        float maxX = width/2.f;
        float maxZ = depth/2.f;

        int vertexCountX = (subdivsX+1);
        int vertexCountZ = (subdivsZ+1);

        int vertexCount = vertexCountX * vertexCountZ;
        int faceCount = subdivsX * subdivsZ * 2; // two triangles per cell
        std::vector<glm::vec3> vertices(vertexCount);
        std::vector<glm::ivec3> faces(faceCount);

        int vertex = 0;
        for (float x = -maxX; x <= maxX; x+=xstep) {
            for (float z = -maxZ; z <= maxZ; z+=zstep) {
                vertices[vertex] = glm::vec3(x, 0, z);
                ++vertex;
            }
        }

        int f = 0;
        for (int x = 0; x < subdivsX; ++x) {
            for (int z = 0; z < subdivsZ; ++z) {
                int v0 = vertexCountZ *  x      + z;
                int v1 = vertexCountZ * (x + 1) + z;
                int v2 = vertexCountZ * (x + 1) + z + 1;
                int v3 = vertexCountZ *  x      + z + 1;

                faces[f] = glm::ivec3(v0, v1, v3);
                faces[f+1] = glm::ivec3(v1, v2, v3);
                f+=2;
            }
        }

        return {vertices, faces, width, depth, subdivsX, subdivsZ};
    }
}