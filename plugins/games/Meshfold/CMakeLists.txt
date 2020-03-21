project(Meshfold)

set(PAX_MESHFOLD_SOURCE_FILES
        src/main.cpp
        src/MeshfoldPlugin.cpp src/properties/PointCloudSprite.cpp src/properties/KeyboardControls.cpp src/MeshfoldSystem.cpp src/Portal.cpp src/Meshfold.cpp)

include_directories(include)
include_directories(../../paxsdl/include)
include_directories(../../paxopengl/include)

set(HEADERS_FOR_CLION
        include/meshfold/MeshfoldPlugin.h
        include/meshfold/MeshfoldGame.h include/meshfold/properties/PointCloudSprite.h include/meshfold/properties/KeyboardControls.h include/meshfold/MeshfoldSystem.h include/meshfold/Portal.h include/meshfold/Meshfold.h)

add_executable(Meshfold ${PAX_MESHFOLD_SOURCE_FILES} ${HEADERS_FOR_CLION})
target_link_libraries(Meshfold paxutil paxsdl paxopengl paxcore)
set_target_properties(Meshfold PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/Demo)