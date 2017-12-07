//
// Created by bittner on 11/20/17.
//

#include <generation/terrain/TerrainGenerator.h>
#include <generation/grid/GridGenerator.h>

namespace PAX {
    void TerrainGenerator::randomizeHeights(Grid &grid) {
        auto heightFunction = [](int x, int z) {
            return static_cast<float>(cos(x) * cos(z));
        };

        for (int x = 0; x < grid.width; ++x) {
            for (int z = 0; z < grid.depth; ++z) {
                grid.getVertexAt(x, z).y = heightFunction(x, z);
            }
        }
    }

    Terrain * TerrainGenerator::generateTerrain() {
        GridGenerator gridGenerator;
        Grid grid = gridGenerator.generateGrid(100, 100, 100, 100);

        randomizeHeights(grid);

        return new Terrain;
    }
}