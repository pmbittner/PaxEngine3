find_package(PythonInterp 3 REQUIRED)
set(SCRIPT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../precompiler/pluginprecompiler.py)
add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/src/Plugin.generated.cpp
        COMMAND ${PYTHON_EXECUTABLE} ${SCRIPT_DIR} PAX ${CMAKE_CURRENT_SOURCE_DIR}/include/ ${CMAKE_CURRENT_SOURCE_DIR}/src/Plugin.generated.cpp
        COMMENT "Precompiling Physics (via Python)"
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/
        VERBATIM
)

include_directories(include)

set(HEADERS_FOR_CLION
        include/Plugin.h
        include/box2d/Box2DPhysicsSystem.h
        include/box2d/Box2DPhysics.h
        include/Physics.h
        include/box2d/Box2DUtils.h
        )
set(PAXPHYSICS_SOURCE src/Physics.cpp src/Plugin.cpp)
set(PAXPHYSICS_LINK_LIBRARIES)

if (WITH_BOX2D)
    set(PAXPHYSICS_SOURCE ${PAXPHYSICS_SOURCE} src/box2d/Box2DPhysicsSystem.cpp src/box2d/Box2DPhysics.cpp)
    set(PAXPHYSICS_LINK_LIBRARIES ${PAXPHYSICS_LINK_LIBRARIES} ${BOX2D_LIBRARY})
endif()

add_library(paxphysics ${HEADERS_FOR_CLION} ${PAXPHYSICS_SOURCE} ${CMAKE_CURRENT_SOURCE_DIR}/src/Plugin.generated.cpp)
target_link_libraries(paxphysics ${PAXPHYSICS_LINK_LIBRARIES})