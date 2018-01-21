//
// Created by Paul on 21.01.2018.
//

#ifndef PAXENGINE3_PHYSICS_H
#define PAXENGINE3_PHYSICS_H

#include <core/entity/EntityComponent.h>

namespace PAX {
    PAX_ENTITYCOMPONENT(Physics, EntityComponent, true)
    class Physics : public EntityComponent {
        PAX_ENTITYCOMPONENT_BODY

    public:
        Physics();
    };
}

#endif //PAXENGINE3_PHYSICS_H
