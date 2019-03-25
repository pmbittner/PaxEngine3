set(PAXPHYSICS_SOURCE src/RigidBody.cpp src/Plugin.cpp)

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

if (WITH_BOX2D)
    set(PAXPHYSICS_SOURCE ${PAXPHYSICS_SOURCE} src/box2d/Box2DPhysicsSystem.cpp src/box2d/Box2DRigidBody.cpp src/Hitbox.cpp src/box2d/Box2DWorld.cpp)
    set(PAXPHYSICS_LINK_LIBRARIES ${PAXPHYSICS_LINK_LIBRARIES} ${BOX2D_LIBRARY})
endif()

add_library(paxphysics ${HEADERS_FOR_CLION} ${PAXPHYSICS_SOURCE})
target_link_libraries(paxphysics ${PAXPHYSICS_LINK_LIBRARIES})