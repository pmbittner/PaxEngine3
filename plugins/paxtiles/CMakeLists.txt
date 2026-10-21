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

add_library(paxtiles ${SOURCE_FILES})
add_library(PaxEngine3::tiles ALIAS paxtiles)
target_include_directories(paxtiles PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_link_libraries(paxtiles PUBLIC paxcore paxphysics)
