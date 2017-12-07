//
// Created by bittner on 11/20/17.
//

#include <generation/grid/GridGenerator.h>
#include <utility/math/Conversion.h>

namespace PAX {
    Grid GridGenerator::generateGrid(float width, float depth, int subdivsX, int subdivsY) {
        float xstep = width / subdivsX;
        float zstep = depth / subdivsY;

        float maxX = width/2.f;
        float maxZ = depth/2.f;

        int vertexCount = (subdivsX+1) * (subdivsY+1);
        int faceCount = subdivsX * subdivsY * 2; // two triangles per cell
        std::vector<glm::vec3> vertices(vertexCount);
        std::vector<glm::ivec3> faces(faceCount);

        int vertex = 0;
        for (int x = -maxX; x < maxX; x+=xstep) {
            for (int z = -maxZ; z < maxZ; z+=zstep) {
                vertices[vertex] = glm::vec3(x, 0, z);
                ++vertex;
            }
        }

        int cellX, cellZ;
        for (int f = 0; f < faceCount; f+=2) {
            cellX = (faceCount/2) / subdivsY;
            cellZ = (faceCount/2) % subdivsY;

            int v0 = Util::Conversion::coordinatesToIndex(subdivsY, cellZ, cellX);
            int v1 = Util::Conversion::coordinatesToIndex(subdivsY, cellZ, cellX + 1);
            int v2 = v1 + 1;
            int v3 = v0 + 1;

            faces[f] = glm::ivec3(v0, v1, v3);
            faces[f+1] = glm::ivec3(v1, v2, v3);
        }

        return {vertices, faces, subdivsX, subdivsY};
    }
}