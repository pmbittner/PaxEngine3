set(PAX_RAYMARCHER_SOURCE_FILES
        src/main.cpp
        src/Plugin.cpp)


add_executable(RayMarcher ${PAX_RAYMARCHER_SOURCE_FILES})
target_link_libraries(RayMarcher PRIVATE paxsdl paxopengl)
target_include_directories(RayMarcher PRIVATE include)
set_target_properties(RayMarcher PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/Demo)
