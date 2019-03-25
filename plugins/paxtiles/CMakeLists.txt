set(HEADERS_FOR_CLION include/paxtiles/Plugin.h include/paxtiles/TileMapProperty.h include/paxtiles/TileMap.h include/paxtiles/Tile.h include/paxtiles/TileMapGraphics.h)
set(SOURCE_FILES src/Plugin.cpp ${HEADERS_FOR_CLION} src/TileMapProperty.cpp src/TileMap.cpp src/TileMapGraphics.cpp)

include_directories(include)
add_library(paxtiles ${SOURCE_FILES})