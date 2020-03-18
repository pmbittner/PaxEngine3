project(RayMarcher)

set(PAX_RAYMARCHER_SOURCE_FILES
        src/main.cpp
        src/Plugin.cpp)

include_directories(include)
include_directories(../../paxsdl/include)
include_directories(../../paxopengl/include)

set(HEADERS_FOR_CLION
        include/raymarcher/Plugin.h
        include/raymarcher/Demo.h)

add_executable(RayMarcher ${PAX_RAYMARCHER_SOURCE_FILES} ${HEADERS_FOR_CLION})
target_link_libraries(RayMarcher paxutil paxsdl paxopengl paxcore)
set_target_properties(RayMarcher PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/Demo)