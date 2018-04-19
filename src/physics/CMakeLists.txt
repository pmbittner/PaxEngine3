set(PAXPHYSICS_SOURCE Physics.cpp)
set(PAXPHYSICS_LINK_LIBRARIES)

if (WITH_BOX2D)
    set(PAXPHYSICS_SOURCE ${PAXPHYSICS_SOURCE} box2d/Box2DPhysicsSystem.cpp box2d/Box2DPhysics.cpp)
    set(PAXPHYSICS_LINK_LIBRARIES ${PAXPHYSICS_LINK_LIBRARIES} ${BOX2D_LIBRARY})
endif()

add_library(paxphysics ${PAXPHYSICS_SOURCE})
target_link_libraries(paxphysics ${PAXPHYSICS_LINK_LIBRARIES})