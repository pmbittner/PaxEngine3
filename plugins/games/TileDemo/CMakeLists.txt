set(PAX_TILEDEMO_SOURCE_FILES
        src/main.cpp
        src/Plugin.cpp)


add_executable(TileDemo ${PAX_TILEDEMO_SOURCE_FILES})
target_link_libraries(TileDemo PRIVATE paxsdl paxopengl paxtiles)
target_include_directories(TileDemo PRIVATE include)
set_target_properties(TileDemo PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/Demo)
