project(PlatformerDemo)

set(PAX_PLATFORMERDEMO_SOURCE_FILES
        src/main.cpp
        src/Plugin.cpp)

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
set(HEADERS_FOR_CLION
        include/Plugin.h
        include/Demo.h
        include/behaviour/FollowEntityBehaviour.h
        include/behaviour/PlayerControls.h
        include/behaviour/PlayerSpriteAnimation.h
        include/behaviour/VelocityBehaviour.h
        include/behaviour/Dance2D.h include/behaviour/DragNDrop.h)

add_executable(PlatformerDemo ${PAX_PLATFORMERDEMO_SOURCE_FILES} ${HEADERS_FOR_CLION} )
target_link_libraries(PlatformerDemo ${EASYLOGGING_LIBRARY} paxphysics paxutil paxsdl paxopengl paxtiles paxcore)
set_target_properties(PlatformerDemo PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../bin/Demo)