set(PAXPHYSICS_LINK_LIBRARIES)

if (WITH_BOX2D)
    add_library(paxbox2dphysics box2d/Box2DPhysicsSystem.cpp box2d/Box2DPhysics.cpp)
    target_link_libraries(paxbox2dphysics ${BOX2D_LIBRARY})

    set(PAXPHYSICS_LINK_LIBRARIES ${PAXPHYSICS_LINK_LIBRARIES} paxbox2dphysics)
endif()

add_library(paxphysics Physics.cpp)
target_link_libraries(paxphysics paxbox2dphysics)