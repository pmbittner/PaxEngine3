//
// Created by Paul on 28.07.2019.
//

#include <paxphysics/2d/box2d/Box2DHitbox.h>

#include <paxcore/Engine.h>
#include <paxcore/Game.h>

namespace PAX::Physics {
    PAX_PROPERTY_IMPL(PAX::Physics::Box2DHitbox)

    Box2DHitbox::Box2DHitbox() : Hitbox2D(nullptr, nullptr) {

    }

    Box2DHitbox::Box2DHitbox(Shape2D * shape, const std::shared_ptr<PhysicsMaterial> &material)
    : Hitbox2D(shape, material)
    {}

    Box2DHitbox::~Box2DHitbox() = default;
}