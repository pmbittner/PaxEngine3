//
// Created by Paul on 28.07.2019.
//

#include <paxphysics/2d/PhysicsWorld2D.h>

namespace PAX::Physics {
    PAX_PROPERTY_IMPL(PAX::Physics::PhysicsWorld2D, PAX_PROPERTY_IS_ABSTRACT)

    void PhysicsWorld2D::initializeFromProvider(PAX::ContentProvider & p) {
        Super::initializeFromProvider(p);
    }

    PhysicsWorld2D::PhysicsWorld2D(const glm::vec2 &gravity) : gravity(gravity) {}

    void PhysicsWorld2D::setGravity(const glm::vec2 &gravity) {
        this->gravity = gravity;
    }

    const glm::vec2& PhysicsWorld2D::getGravity() {
        return gravity;
    }
}