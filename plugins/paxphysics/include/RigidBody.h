//
// Created by Paul on 21.01.2018.
//

#ifndef PAXENGINE3_PHYSICS_H
#define PAXENGINE3_PHYSICS_H

#include <paxcore/entity/EntityComponent.h>

namespace PAX {
    namespace Physics {
        class RigidBody : public EntityComponent {
        PAX_ENTITYCOMPONENT_BODY(EntityComponent, false)

        public:
            RigidBody();
        };
    }
}

#endif //PAXENGINE3_PHYSICS_H
