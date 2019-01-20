project(PlatformerDemo)

set(PAX_PLATFORMERDEMO_SOURCE_FILES
        src/main.cpp
        src/Plugin.cpp src/behaviour/VelocityBehaviour.cpp src/behaviour/DragNDrop.cpp src/behaviour/ProfileGameLoopBehaviour.cpp src/behaviour/Dance2D.cpp src/behaviour/PlayerSpriteAnimation.cpp src/behaviour/PlayerControls.cpp src/behaviour/FollowEntityBehaviour.cpp)

if (PAX_RUN_PYTHON_PRECOMPILER)
    find_package(PythonInterp 3 REQUIRED)
    set(SCRIPT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../precompiler/pluginprecompiler.py)
    add_custom_command(
            OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/src/Plugin.generated.cpp
            COMMAND ${PYTHON_EXECUTABLE} ${SCRIPT_DIR} PAX::PlatformerDemo ${CMAKE_CURRENT_SOURCE_DIR}/include/ ${CMAKE_CURRENT_SOURCE_DIR}/src/Plugin.generated.cpp
            COMMENT "Precompiling ${PROJECT_NAME} (via Python)"
            DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/
            VERBATIM
    )
    set(PAX_PLATFORMERDEMO_SOURCE_FILES
            ${PAX_PLATFORMERDEMO_SOURCE_FILES}
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Plugin.generated.cpp)
endif (PAX_RUN_PYTHON_PRECOMPILER)

include_directories(include)
include_directories(../paxsdl/include)
include_directories(../paxopengl/include)
include_directories(../paxphysics/include)
include_directories(../paxtiles/include)

set(HEADERS_FOR_CLION
        include/platformerdemo/Plugin.h
        include/platformerdemo/Demo.h
        include/platformerdemo/behaviour/FollowEntityBehaviour.h
        include/platformerdemo/behaviour/PlayerControls.h
        include/platformerdemo/behaviour/PlayerSpriteAnimation.h
        include/platformerdemo/behaviour/VelocityBehaviour.h
        include/platformerdemo/behaviour/Dance2D.h
        include/platformerdemo/behaviour/DragNDrop.h
        include/platformerdemo/behaviour/ProfileGameLoopBehaviour.h)

add_executable(PlatformerDemo ${PAX_PLATFORMERDEMO_SOURCE_FILES} ${HEADERS_FOR_CLION} )
target_link_libraries(PlatformerDemo ${EASYLOGGING_LIBRARY} paxphysics paxutil paxsdl paxopengl paxtiles paxcore)
set_target_properties(PlatformerDemo PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../bin/Demo)