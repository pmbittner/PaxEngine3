//
// Created by Paul on 22.03.2019.
//

#ifndef PAXENGINE3_HITBOX_H
#define PAXENGINE3_HITBOX_H

#include <paxcore/entity/EntityComponent.h>

namespace PAX {
    namespace Physics {
        class Hitbox : public EntityComponent {
            PAX_PROPERTY(PAX::Physics::Hitbox, PAX_PROPERTY_IS_ABSTRACT)
            PAX_PROPERTY_DERIVES(PAX::EntityComponent)
            PAX_PROPERTY_IS_SINGLE

        public:
            ~Hitbox() override;
        };
    }
}

#endif //PAXENGINE3_HITBOX_H
