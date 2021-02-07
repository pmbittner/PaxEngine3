set(HEADERS_FOR_CLION
        include/paxtiles/Plugin.h
        include/paxtiles/TileMapProperty.h
        include/paxtiles/TileMap.h
        include/paxtiles/Tile.h
        include/paxtiles/TileMapGraphics.h
        include/paxtiles/tiled/TileMapJsonLoader.h
        include/paxtiles/TileSet.h
        include/paxtiles/tiled/TileSetJsonLoader.h
        include/paxtiles/topdown/CharacterOrientation.h
        include/paxtiles/topdown/CharacterSpriteAnimation.h
        include/paxtiles/topdown/SimpleCharacterKeyboardControls.h
        include/paxtiles/TileMapTransition.h)

set(SOURCE_FILES
        src/Plugin.cpp
        src/TileMapProperty.cpp
        src/TileMap.cpp
        src/TileMapGraphics.cpp
        src/tiled/TileMapJsonLoader.cpp
        src/tiled/TileSetJsonLoader.cpp
        src/TileSet.cpp
        src/topdown/CharacterOrientation.cpp
        src/topdown/CharacterSpriteAnimation.cpp
        src/topdown/SimpleCharacterKeyboardControls.cpp
        src/TileMapTransition.cpp)

include_directories(include)
include_directories(../paxphysics/include)

add_library(paxtiles ${SOURCE_FILES} ${HEADERS_FOR_CLION})
target_link_libraries(paxtiles paxphysics)