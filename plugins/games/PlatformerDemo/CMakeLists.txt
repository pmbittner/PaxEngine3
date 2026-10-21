set(PAX_PLATFORMERDEMO_SOURCE_FILES
        src/main.cpp
        src/Plugin.cpp
        src/behaviour/DragNDrop.cpp
        src/behaviour/ProfileGameLoopBehaviour.cpp
        src/behaviour/Dance2D.cpp
        src/behaviour/PlayerSpriteAnimation.cpp
        src/behaviour/PlayerControls.cpp
        )


add_executable(PlatformerDemo ${PAX_PLATFORMERDEMO_SOURCE_FILES})
target_link_libraries(PlatformerDemo PRIVATE paxsdl paxopengl paxphysics paxtiles)
target_include_directories(PlatformerDemo PRIVATE include)
set_target_properties(PlatformerDemo PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/Demo)
