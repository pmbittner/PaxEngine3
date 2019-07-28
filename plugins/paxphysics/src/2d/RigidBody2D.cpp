//
// Created by Paul on 21.01.2018.
//

#include "paxphysics/2d/RigidBody2D.h"

namespace PAX::Physics {
    PAX_PROPERTY_SOURCE(PAX::Physics::RigidBody2D, PAX_PROPERTY_IS_ABSTRACT)

    void RigidBody2D::initializeFromProvider(ContentProvider & provider) {
        Super::initializeFromProvider(provider);
    }

    RigidBody2D::RigidBody2D() = default;
}