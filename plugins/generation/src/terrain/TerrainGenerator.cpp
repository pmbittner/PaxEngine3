//
// Created by bittner on 11/20/17.
//

#include <generation/terrain/TerrainGenerator.h>
#include <generation/grid/GridGenerator.h>
#include <resource/OpenGLMesh.h>

namespace PAX {
    void TerrainGenerator::randomizeHeights(Grid &grid) {
        auto heightFunction = [](int x, int z) {
            return (1+static_cast<float>(cos(x) * sin(z)))/2.f;
        };

        float xstep = grid.width / grid.subdivsX;
        float zstep = grid.depth / grid.subdivsZ;

        float maxX =  grid.width/2.f;
        float maxZ =  grid.depth/2.f;

        for (int x = 0; x <= grid.subdivsX; ++x) {
            for (int z = 0; z <= grid.subdivsZ; ++z) {
                grid.getVertexAt(x,z).y = heightFunction(
                        floor(((x / ((float)grid.subdivsX)) - .5f) * grid.width),
                        floor(((z / ((float)grid.subdivsZ)) - .5f) * grid.depth)
                );
            }
        }

        /*
        for (float x = -maxX; x <= maxX; x+=xstep) {
            for (float z = -maxZ; z <= maxZ; z+=zstep) {
                grid.getVertexAt(
                        ((x + maxX) /  grid.width) * grid.subdivsX,
                        ((z + maxZ) /  grid.depth) * grid.subdivsZ
                ).y = heightFunction(x, z);
            }
        }
         //*/
    }

    Terrain * TerrainGenerator::generateTerrain() {
        GridGenerator gridGenerator;
        Grid grid = gridGenerator.generateGrid(40, 40, 1000, 1000);

        randomizeHeights(grid);

        /*
        std::vector<glm::vec3> vertices = {
                {-0.5f,0.5f,-0.5f},
                {-0.5f,-0.5f,-0.5f},
                {0.5f,-0.5f,-0.5f},
                {0.5f,0.5f,-0.5f},
                {-0.5f,0.5f,0.5f},
                {-0.5f,-0.5f,0.5f},
                {0.5f,-0.5f,0.5f},
                {0.5f,0.5f,0.5f}
        };

        std::vector<std::vector<int>> faces = {
                {0,1,3},
                {3,1,2},
                {4,5,7},
                {7,5,6},
                {3,2,7},
                {7,2,6},
                {0,1,4},
                {4,1,5},
                {4,0,7},
                {7,0,3},
                {5,1,6},
                {6,1,2}
        };*/

        OpenGL::OpenGLMesh* mesh = new OpenGL::OpenGLMesh(grid.vertices, grid.faces);
        mesh->finalize();
        mesh->upload();

        return new Terrain(mesh);
    }
}