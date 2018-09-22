//
// Created by Paul on 11.05.2017.
//

#ifndef PAXENGINE3_ENTITYCOMPONENTADDEDEVENT_H
#define PAXENGINE3_ENTITYCOMPONENTADDEDEVENT_H

#include "../Entity.h"
#include "EntityComponentEvent.h"

namespace PAX {
    template <class EntityComponentType>
    struct EntityComponentAddedEvent : public EntityComponentEvent<EntityComponentType> {
    public:
        EntityComponentAddedEvent(
                const std::shared_ptr<EntityComponentType> & component, Entity* entity)
                : EntityComponentEvent<EntityComponentType>(component, entity) {}
    };
}

#endif //PAXENGINE3_ENTITYCOMPONENTADDEDEVENT_H
