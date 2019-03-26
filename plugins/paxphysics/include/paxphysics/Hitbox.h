//
// Created by Paul on 22.03.2019.
//

#ifndef PAXENGINE3_HITBOX_H
#define PAXENGINE3_HITBOX_H

#include <paxcore/entity/EntityProperty.h>

namespace PAX {
    namespace Physics {
        class Hitbox : public EntityProperty {
            PAX_PROPERTY(PAX::Physics::Hitbox, PAX_PROPERTY_IS_ABSTRACT)
            PAX_PROPERTY_DERIVES(PAX::EntityProperty)
            PAX_PROPERTY_IS_SINGLE

        public:
            ~Hitbox() override;
        };
    }
}

#endif //PAXENGINE3_HITBOX_H
