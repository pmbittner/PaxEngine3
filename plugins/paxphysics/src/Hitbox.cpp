//
// Created by Paul on 22.03.2019.
//

#include <paxphysics/Hitbox.h>

namespace PAX {
    namespace Physics {
        PAX_PROPERTY_SOURCE(PAX::Physics::Hitbox, PAX_PROPERTY_IS_ABSTRACT)

        Hitbox::~Hitbox() = default;
    }
}