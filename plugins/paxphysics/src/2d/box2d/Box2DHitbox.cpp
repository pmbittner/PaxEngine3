//
// Created by Paul on 28.07.2019.
//

#include <paxphysics/2d/box2d/Box2DHitbox.h>
#include <paxphysics/2d/box2d/Box2DWorld.h>
#include <Box2D/Dynamics/b2Body.h>
#include <paxphysics/2d/box2d/Box2DUtils.h>

#include <paxcore/Engine.h>
#include <paxcore/Game.h>
#include <paxphysics/2d/box2d/Box2DPhysicsSystem.h>

namespace PAX::Physics {
    PAX_PROPERTY_IMPL(PAX::Physics::Box2DHitbox)

    Box2DHitbox::Box2DHitbox() : Hitbox2D() {

    }

    Box2DHitbox::~Box2DHitbox() = default;
}