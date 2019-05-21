//
// Created by Paul on 22.03.2019.
//

#include <paxphysics/Hitbox.h>

namespace PAX {
    namespace Physics {
        PAX_PROPERTY_SOURCE(PAX::Physics::Hitbox, PAX_PROPERTY_IS_ABSTRACT)

        void Hitbox::initializeFromProvider(ContentProvider & provider) {
            Super::initializeFromProvider(provider);
        }

        Hitbox::~Hitbox() = default;
    }
}