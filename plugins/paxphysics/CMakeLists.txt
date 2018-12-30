set(PAXPHYSICS_SOURCE src/RigidBody.cpp src/Plugin.cpp)

if (PAX_RUN_PYTHON_PRECOMPILER)
    find_package(PythonInterp 3 REQUIRED)
    set(SCRIPT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../precompiler/pluginprecompiler.py)
    add_custom_command(
            OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/src/Plugin.generated.cpp
            COMMAND ${PYTHON_EXECUTABLE} ${SCRIPT_DIR} PAX::Physics ${CMAKE_CURRENT_SOURCE_DIR}/include/ ${CMAKE_CURRENT_SOURCE_DIR}/src/Plugin.generated.cpp
            COMMENT "Precompiling PAX::Physics (via Python)"
            DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/
            VERBATIM
    )
    set(PAXPHYSICS_SOURCE ${PAXPHYSICS_SOURCE} ${CMAKE_CURRENT_SOURCE_DIR}/src/Plugin.generated.cpp)
endif (PAX_RUN_PYTHON_PRECOMPILER)

include_directories(include)

set(HEADERS_FOR_CLION
        include/Plugin.h
        include/box2d/Box2DPhysicsSystem.h
        include/box2d/Box2DRigidBody.h
        include/RigidBody.h
        include/box2d/Box2DUtils.h
        include/box2d/Box2DWorld.h
        )
set(PAXPHYSICS_LINK_LIBRARIES)

if (WITH_BOX2D)
    set(PAXPHYSICS_SOURCE ${PAXPHYSICS_SOURCE} src/box2d/Box2DPhysicsSystem.cpp src/box2d/Box2DRigidBody.cpp)
    set(PAXPHYSICS_LINK_LIBRARIES ${PAXPHYSICS_LINK_LIBRARIES} ${BOX2D_LIBRARY})
endif()

add_library(paxphysics ${HEADERS_FOR_CLION} ${PAXPHYSICS_SOURCE})
target_link_libraries(paxphysics ${PAXPHYSICS_LINK_LIBRARIES})