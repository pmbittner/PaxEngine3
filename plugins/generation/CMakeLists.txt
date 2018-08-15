set(HEADERS_FOR_CLION
        include/generation/terrain/TerrainGenerator.h
        include/generation/terrain/Terrain.h
        include/generation/grid/GridGenerator.h
        include/generation/grid/Grid.h
        )

add_library(paxgeneration ${HEADERS_FOR_CLION}
        src/terrain/TerrainGenerator.cpp src/terrain/Terrain.cpp src/grid/GridGenerator.cpp)
target_link_libraries(paxgeneration)