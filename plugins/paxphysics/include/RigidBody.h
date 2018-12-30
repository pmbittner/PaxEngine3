//
// Created by Paul on 21.01.2018.
//

#ifndef PAXENGINE3_PHYSICS_H
#define PAXENGINE3_PHYSICS_H

#include <paxcore/entity/EntityComponent.h>

namespace PAX {
    namespace Physics {
        class RigidBody : public EntityComponent {
        PAX_PROPERTY_DERIVES(EntityComponent)
        PAX_PROPERTY_IS_SINGLE

        public:
            RigidBody();
        };
    }
}

#endif //PAXENGINE3_PHYSICS_H
