//
// Created by Paul on 11.05.2017.
//

#ifndef PAXENGINE3_ENTITYCOMPONENTEVENT_H
#define PAXENGINE3_ENTITYCOMPONENTEVENT_H

#include "../Entity.h"
#include "EntityEvent.h"

namespace PAX {
    template <class EntityComponentType>
    struct EntityComponentEvent : public EntityEvent {
    public:
        EntityComponentType* _component;
        EntityComponentEvent(EntityComponentType * component, Entity *entity) : EntityEvent(entity), _component(component) {}
    };
}

#endif //PAXENGINE3_ENTITYCOMPONENTEVENT_H
