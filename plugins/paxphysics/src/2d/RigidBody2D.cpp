//
// Created by Paul on 21.01.2018.
//

#include "paxphysics/2d/RigidBody2D.h"

namespace PAX::Physics {
    PAX_PROPERTY_IMPL(PAX::Physics::RigidBody2D)

    ClassMetadata RigidBody2D::getMetadata() {
        ClassMetadata m = Super::getMetadata();
        m.add(paxfieldof(fixedRotation));
        return m;
    }

    bool RigidBody2D::hasFixedRotation() const {
        return fixedRotation;
    }

    void RigidBody2D::setFixedRotation(bool fixedRotation) {
        this->fixedRotation = fixedRotation;
    }
}