//
// Created by Paul on 11.05.2017.
//

#ifndef PAXENGINE3_ENTITYCOMPONENTREMOVEDEVENT_H
#define PAXENGINE3_ENTITYCOMPONENTREMOVEDEVENT_H

#include "../Entity.h"
#include "EntityComponentEvent.h"

namespace PAX {
    template <class EntityComponentType>
    struct EntityComponentRemovedEvent : public EntityComponentEvent<EntityComponentType> {
    public:
        EntityComponentRemovedEvent(EntityComponentType * component, Entity *entity) : EntityComponentEvent<EntityComponentType>(component, entity) {}
    };
}

#endif //PAXENGINE3_ENTITYCOMPONENTREMOVEDEVENT_H
