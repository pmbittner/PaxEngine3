set(HEADERS_FOR_CLION include/paxtiles/Plugin.h include/paxtiles/TileMapProperty.h include/paxtiles/TileMap.h include/paxtiles/Tile.h include/paxtiles/TileMapGraphics.h include/paxtiles/tiled/TiledMapJsonLoader.h include/paxtiles/TileSet.h include/paxtiles/tiled/TileSetJsonLoader.h)
set(SOURCE_FILES src/Plugin.cpp ${HEADERS_FOR_CLION} src/TileMapProperty.cpp src/TileMap.cpp src/TileMapGraphics.cpp src/tiled/TiledMapJsonLoader.cpp src/tiled/TileSetJsonLoader.cpp src/TileSet.cpp)

include_directories(include)
add_library(paxtiles ${SOURCE_FILES})