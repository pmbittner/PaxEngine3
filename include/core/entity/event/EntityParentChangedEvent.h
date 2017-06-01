//
// Created by paul on 01.06.17.
//

#ifndef PAXENGINE3_ENTITYPARENTCHANGEDEVENT_H
#define PAXENGINE3_ENTITYPARENTCHANGEDEVENT_H

#include "EntityEvent.h"

namespace PAX {
    class EntityParentChangedEvent : public EntityEvent {
    public:
        Entity *newParent, *oldParent;
        EntityParentChangedEvent(Entity *entity, Entity *oldParent, Entity *newParent) : EntityEvent(entity), oldParent(oldParent), newParent(newParent) {}
    };
}

#endif //PAXENGINE3_ENTITYPARENTCHANGEDEVENT_H
