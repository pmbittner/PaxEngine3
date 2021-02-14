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
        src/2d/gravityfields/GravityFieldSystem.cpp src/2d/gravityfields/GravityFieldSensitive.cpp src/2d/gravityfields/GravityFieldRegister.cpp)

include_directories(include)

set(HEADERS_FOR_CLION
        include/paxphysics/Plugin.h
        include/paxphysics/2d/box2d/Box2DPhysicsSystem.h
        include/paxphysics/2d/box2d/Box2DRigidBody.h
        include/paxphysics/2d/RigidBody2D.h
        include/paxphysics/2d/box2d/Box2DUtils.h
        include/paxphysics/2d/box2d/Box2DWorld.h
        include/paxphysics/2d/Hitbox2D.h
        include/paxphysics/2d/shape/Shape2D.h
        include/paxphysics/2d/shape/Rectangle.h
        include/paxphysics/2d/PhysicsWorld2D.h
        include/paxphysics/2d/box2d/Box2DHitbox.h
        include/paxphysics/2d/material/PhysicsMaterial.h
        include/paxphysics/2d/material/PhysicsMaterialLoader.h
        include/paxphysics/2d/gravityfields/GravityField.h
        include/paxphysics/2d/gravityfields/SphereGravityField.h
        include/paxphysics/2d/visualization/HitboxGraphics.h
        include/paxphysics/2d/json/JsonShape2DParser.h
        include/paxphysics/2d/shape/Circle.h
        include/paxphysics/2d/gravityfields/DirectionalGravityField.h
        include/paxphysics/2d/gravityfields/GravityFieldSystem.h
        include/paxphysics/2d/gravityfields/GravityFieldSensitive.h include/paxphysics/2d/PhysicsSystem2D.h include/paxphysics/2d/gravityfields/GravityFieldRegister.h)
set(PAXPHYSICS_LINK_LIBRARIES)

set(PAX_BOX2D_PATH ${PAX_LIB_DIR}/box2d)
set(BOX2D_INCLUDE_DIRS ${PAX_BOX2D_PATH}/include)

if (WIN32 AND ${PAX_COMPILER_IS_MSVC})
    if(${CMAKE_BUILD_TYPE} MATCHES Debug)
        message("Building paxphysics with MSVC - Debug")
        set(BOX2D_LIBRARY ${PAX_BOX2D_PATH}/bin/msvc-debug/bin/box2d.lib)
    else()
        message("Building paxphysics with MSVC - Release")
        set(BOX2D_LIBRARY ${PAX_BOX2D_PATH}/bin/msvc-release/bin/box2d.lib)
    endif(${CMAKE_BUILD_TYPE} MATCHES Debug)
else()
    if(${CMAKE_BUILD_TYPE} MATCHES Debug)
        message("Building paxphysics - Debug")
        set(BOX_LIB_DIR ${PAX_LIB_DIR}/bin/build-debug/bin)
    else()
        message("Building paxphysics - Release")
        set(BOX_LIB_DIR ${PAX_LIB_DIR}/bin/build-release/bin)
    endif(${CMAKE_BUILD_TYPE} MATCHES Debug)
    set(BOX2D_LIBRARY ${BOX_LIB_DIR}/libbox2d.a)
endif()

include_directories(${BOX2D_INCLUDE_DIRS})

add_library(paxphysics ${HEADERS_FOR_CLION} ${PAXPHYSICS_SOURCE})
target_link_libraries(paxphysics ${BOX2D_LIBRARY})