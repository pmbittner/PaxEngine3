project(Meshfold)

set(PAX_MESHFOLD_SOURCE_FILES
        src/main.cpp
        src/Plugin.cpp src/PointCloudSprite.cpp)

include_directories(include)
include_directories(../../paxsdl/include)
include_directories(../../paxopengl/include)

set(HEADERS_FOR_CLION
        include/meshfold/Plugin.h
        include/meshfold/Meshfold.h include/meshfold/PointCloudSprite.h)

add_executable(Meshfold ${PAX_MESHFOLD_SOURCE_FILES} ${HEADERS_FOR_CLION})
target_link_libraries(Meshfold paxutil paxsdl paxopengl paxcore)
set_target_properties(Meshfold PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/Demo)