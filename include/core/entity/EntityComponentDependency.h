//
// Created by Paul on 16.07.2017.
//

#ifndef PAXENGINE3_ENTITYCOMPONENTDEPENDENCY_H
#define PAXENGINE3_ENTITYCOMPONENTDEPENDENCY_H

#include "../../utility/Dependency.h"

namespace PAX {
    class Entity;
    //template<typename ComponentClass>
    //bool Entity::has();
    //template<typename FirstComponentClass, typename SecondComponentClass, typename... ComponentClass>
    //bool Entity::has();

    template<class... EntityComponentTypes>
    class EntityComponentDependency : public Dependency<Entity> {
    public:
        bool met(const Entity *entity) const {
            //return entity->has<EntityComponentTypes...>();
            return true;
        }
    };
}

#endif //PAXENGINE3_ENTITYCOMPONENTDEPENDENCY_H
