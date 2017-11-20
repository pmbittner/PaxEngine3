//
// Created by bittner on 11/20/17.
//

#include <generation/grid/GridGenerator.h>

namespace PAX {
    CPUMesh GridGenerator::generateGrid(float width, float depth, int subdivsX, int subdivsY) {
        float xstep = width / subdivsX;
        float zstep = depth / subdivsY;
        int columns = width / xstep;
        int rows = depth / zstep;
        int vertexCount = (columns+1) * (rows+1);
        std::vector<glm::vec3> vertices;

        return {};
    }
}