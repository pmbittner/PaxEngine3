//
// Created by Paul on 28.07.2019.
//

#include <paxphysics/2d/PhysicsWorld2D.h>

namespace PAX::Physics {
    PAX_PROPERTY_IMPL(PAX::Physics::PhysicsWorld2D)

    PhysicsWorld2D::PhysicsWorld2D(const glm::vec2 &gravity) : gravity(gravity) {}

    ClassMetadata PhysicsWorld2D::getMetadata() {
        ClassMetadata m = Super::getMetadata();
        m.add(paxfieldof(gravity)).addFlag(Field::IsMandatory);
        return m;
    }

    void PhysicsWorld2D::setGravity(const glm::vec2 &gravity) {
        this->gravity = gravity;
    }

    const glm::vec2& PhysicsWorld2D::getGravity() {
        return gravity;
    }
}