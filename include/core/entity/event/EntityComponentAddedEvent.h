//
// Created by Paul on 11.05.2017.
//

#ifndef PAXENGINE3_ENTITYCOMPONENTADDEDEVENT_H
#define PAXENGINE3_ENTITYCOMPONENTADDEDEVENT_H

#include "../Entity.h"
#include "EntityComponentEvent.h"

namespace PAX {
    template <class EntityComponentType>
    class EntityComponentAddedEvent : public EntityComponentEvent<EntityComponentType> {
    public:
        EntityComponentAddedEvent(EntityComponentType * component, Entity *entity) : EntityComponentEvent<EntityComponentType>(component, entity) {}
    };
}

#endif //PAXENGINE3_ENTITYCOMPONENTADDEDEVENT_H
