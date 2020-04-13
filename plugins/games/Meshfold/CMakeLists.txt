project(Meshfold)

set(PAX_MESHFOLD_SOURCE_FILES
        src/main.cpp

        src/MeshfoldPlugin.cpp
        src/properties/PointCloudSprite.cpp
        src/properties/KeyboardControls.cpp

        src/MeshfoldSystem.cpp
        src/Portal.cpp
        src/Meshfold.cpp
        src/PortalGenerator.cpp src/MeshfoldGame.cpp src/util/AssetUtils.cpp)

include_directories(include)
include_directories(../../paxsdl/include)
include_directories(../../paxopengl/include)
include_directories(../../paxassetimport/include)

set(HEADERS_FOR_CLION
        include/meshfold/MeshfoldPlugin.h
        include/meshfold/MeshfoldGame.h
        include/meshfold/properties/PointCloudSprite.h
        include/meshfold/properties/KeyboardControls.h
        include/meshfold/MeshfoldSystem.h
        include/meshfold/Portal.h
        include/meshfold/Meshfold.h
        include/meshfold/PortalGenerator.h include/meshfold/util/AssetUtils.h)

add_executable(Meshfold ${PAX_MESHFOLD_SOURCE_FILES} ${HEADERS_FOR_CLION})
target_link_libraries(Meshfold paxutil paxsdl paxopengl paxassimp paxcore)
set_target_properties(Meshfold PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/Demo)