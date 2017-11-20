//
// Created by bittner on 11/20/17.
//

#include <generation/terrain/TerrainGenerator.h>
#include <generation/grid/GridGenerator.h>

namespace PAX {
    Terrain * TerrainGenerator::generateTerrain() {
        GridGenerator gridGenerator;
        CPUMesh mesh = gridGenerator.generateGrid(100, 100, 100, 100);

        return new Terrain;
    }
}