//
// Created by Paul on 08.05.2017.
//

#ifndef PAXENGINE3_ENTITYDESPAWNEDEVENT_H
#define PAXENGINE3_ENTITYDESPAWNEDEVENT_H

#include "../../entity/Entity.h"
#include "../../entity/event/EntityEvent.h"

namespace PAX {
    class EntityDespawnedEvent : public EntityEvent {
    public:
        EntityDespawnedEvent(Entity *entity) : EntityEvent(entity) {}
    };
}

#endif //PAXENGINE3_ENTITYDESPAWNEDEVENT_H
