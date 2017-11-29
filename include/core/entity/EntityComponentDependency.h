//
// Created by Paul on 16.07.2017.
//

#ifndef PAXENGINE3_ENTITYCOMPONENTDEPENDENCY_H
#define PAXENGINE3_ENTITYCOMPONENTDEPENDENCY_H

#include "../../utility/Dependency.h"

namespace PAX {
    class Entity;

    template<class... EntityComponentTypes>
    class EntityComponentDependency : public Dependency<Entity> {
    public:
        bool met(const Entity *entity) const {
            return entity->has<EntityComponentTypes...>();
        }
    };
}

#endif //PAXENGINE3_ENTITYCOMPONENTDEPENDENCY_H
