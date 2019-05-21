//
// Created by Paul on 21.01.2018.
//

#include "paxphysics/RigidBody.h"

namespace PAX {
    namespace Physics {
        PAX_PROPERTY_SOURCE(PAX::Physics::RigidBody, PAX_PROPERTY_IS_ABSTRACT)

        void RigidBody::initializeFromProvider(ContentProvider & provider) {
            Super::initializeFromProvider(provider);
        }

        RigidBody::RigidBody() = default;
    }
}