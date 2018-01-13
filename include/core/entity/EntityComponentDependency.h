//
// Created by Paul on 16.07.2017.
//

#ifndef PAXENGINE3_ENTITYCOMPONENTDEPENDENCY_H
#define PAXENGINE3_ENTITYCOMPONENTDEPENDENCY_H

#include "../../utility/Dependency.h"
#include "Entity.h"

namespace PAX {
    class Entity;

    template<class... EntityComponentTypes>
    class EntityComponentDependency : public Dependency<Entity> {
    public:
        virtual bool met(const Entity *entity) const override {
            return entity->has<EntityComponentTypes...>();
            //return true;
        }
    };

    template<>
    class EntityComponentDependency<> : public Dependency<Entity> {
    };
}

#endif //PAXENGINE3_ENTITYCOMPONENTDEPENDENCY_H
