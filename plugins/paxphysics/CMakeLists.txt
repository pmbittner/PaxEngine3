find_package(box2d REQUIRED)

set(PAXPHYSICS_SOURCE
        src/2d/RigidBody2D.cpp
        src/Plugin.cpp
        src/2d/box2d/Box2DPhysicsSystem.cpp
        src/2d/box2d/Box2DRigidBody.cpp
        src/2d/Hitbox2D.cpp
        src/2d/box2d/Box2DWorld.cpp
        src/2d/gravityfields/GravityField.cpp
        src/2d/gravityfields/SphereGravityField.cpp
        src/2d/visualization/HitboxGraphics.cpp
        src/2d/box2d/Box2DUtils.cpp
        src/2d/shape/Shape2D.cpp
        src/2d/shape/Rectangle.cpp
        src/2d/PhysicsWorld2D.cpp
        src/2d/box2d/Box2DHitbox.cpp
        src/2d/material/PhysicsMaterialLoader.cpp
        src/2d/material/PhysicsMaterial.cpp
        src/2d/json/JsonShape2DParser.cpp
        src/2d/shape/Circle.cpp
        src/2d/gravityfields/DirectionalGravityField.cpp
        src/2d/gravityfields/GravityFieldSystem.cpp
        src/2d/gravityfields/GravityFieldSensitive.cpp
        src/2d/gravityfields/GravityFieldRegister.cpp
        src/2d/event/Collision.cpp)

add_library(paxphysics ${PAXPHYSICS_SOURCE})
add_library(PaxEngine3::physics ALIAS paxphysics)
target_include_directories(paxphysics PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_link_libraries(paxphysics PUBLIC paxcore box2d::box2d)
