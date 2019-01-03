set(HEADERS_FOR_CLION include/Plugin.h include/paxtiles/TileMapProperty.h include/paxtiles/TileMap.h include/paxtiles/Tile.h include/paxtiles/TileMapGraphics.h)
set(SOURCE_FILES src/Plugin.cpp ${HEADERS_FOR_CLION} src/TileMapProperty.cpp src/TileMap.cpp src/TileMapGraphics.cpp)

if (PAX_RUN_PYTHON_PRECOMPILER)
    find_package(PythonInterp 3 REQUIRED)
    set(SCRIPT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../precompiler/pluginprecompiler.py)
    add_custom_command(
            OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/src/Plugin.generated.cpp
            COMMAND ${PYTHON_EXECUTABLE} ${SCRIPT_DIR} PAX::Tiles ${CMAKE_CURRENT_SOURCE_DIR}/include/ ${CMAKE_CURRENT_SOURCE_DIR}/src/Plugin.generated.cpp
            COMMENT "Precompiling PAX::Tiles (via Python)"
            DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/
            VERBATIM
    )

    set(SOURCE_FILES ${SOURCE_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/src/Plugin.generated.cpp)
endif (PAX_RUN_PYTHON_PRECOMPILER)

include_directories(include)
add_library(paxtiles ${SOURCE_FILES})