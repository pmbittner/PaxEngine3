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

    if(${CMAKE_BUILD_TYPE} MATCHES Debug)
        message("Building paxphysics with MSVC - Debug")
        set(BOX2D_LIBRARY ${PAX_LIB_DIR}/Box2D/bin/msvc-debug/box2d.lib)
    else()
        message("Building paxphysics with MSVC - Release")
        set(BOX2D_LIBRARY ${PAX_LIB_DIR}/Box2D/bin/msvc-release/box2d.lib)
    endif(${CMAKE_BUILD_TYPE} MATCHES Debug)
else()
    include_directories(${PAX_LIB_DIR}/Box2D)

    if(${CMAKE_BUILD_TYPE} MATCHES Debug)
        message("Building paxphysics - Debug")
        set(BOX_LIB_DIR ${PAX_LIB_DIR}/Box2D/bin/build-debug)
    else()
        message("Building paxphysics - Release")
        set(BOX_LIB_DIR ${PAX_LIB_DIR}/Box2D/bin/build-release)
    endif(${CMAKE_BUILD_TYPE} MATCHES Debug)
    set(BOX2D_LIBRARY ${BOX_LIB_DIR}/libbox2d.a)
endif()

add_library(paxphysics ${HEADERS_FOR_CLION} ${PAXPHYSICS_SOURCE})
target_link_libraries(paxphysics ${BOX2D_LIBRARY})