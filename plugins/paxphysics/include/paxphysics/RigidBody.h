//
// Created by Paul on 21.01.2018.
//

#ifndef PAXENGINE3_PHYSICS_H
#define PAXENGINE3_PHYSICS_H

#include <paxcore/entity/EntityProperty.h>

namespace PAX {
    namespace Physics {
        class RigidBody : public EntityProperty {
            PAX_PROPERTY(RigidBody, PAX_PROPERTY_IS_ABSTRACT)
            PAX_PROPERTY_DERIVES(EntityProperty)
            PAX_PROPERTY_IS_MULTIPLE

        public:
            RigidBody();
        };
    }
}

#endif //PAXENGINE3_PHYSICS_H
