set(PAXPHYSICS_SOURCE
        src/RigidBody.cpp
        src/Plugin.cpp
        src/box2d/Box2DPhysicsSystem.cpp
        src/box2d/Box2DRigidBody.cpp
        src/Hitbox.cpp
        src/box2d/Box2DWorld.cpp)

include_directories(include)

set(HEADERS_FOR_CLION
        include/paxphysics/Plugin.h
        include/paxphysics/box2d/Box2DPhysicsSystem.h
        include/paxphysics/box2d/Box2DRigidBody.h
        include/paxphysics/RigidBody.h
        include/paxphysics/box2d/Box2DUtils.h
        include/paxphysics/box2d/Box2DWorld.h
        include/paxphysics/Hitbox.h)
set(PAXPHYSICS_LINK_LIBRARIES)

if (WIN32 AND ${PAX_COMPILER_IS_MSVC})
    include_directories(${PAX_LIB_DIR}/Box2D)
    set(BOX2D_LIBRARY ${PAX_LIB_DIR}/Box2D/bin/msvc/box2d.lib)
else()
    include_directories(${PAX_LIB_DIR}/Box2D)
    link_directories(${PAX_LIB_DIR}/Box2D/bin/mingw)
    set(BOX2D_LIBRARY box2d)
endif()

add_library(paxphysics ${HEADERS_FOR_CLION} ${PAXPHYSICS_SOURCE})
target_link_libraries(paxphysics ${BOX2D_LIBRARY})