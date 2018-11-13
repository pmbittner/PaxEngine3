//
// Created by Paul on 08.05.2017.
//

#ifndef PAXENGINE3_ENTITYDESPAWNEDEVENT_H
#define PAXENGINE3_ENTITYDESPAWNEDEVENT_H

#include "../../entity/Entity.h"
#include "../../entity/event/EntityEvent.h"

namespace PAX {
    struct EntityDespawnedEvent : public EntityEvent {
        WorldLayer* oldWorldLayer = nullptr;
        EntityDespawnedEvent(Entity *entity, WorldLayer* oldWorldLayer) : EntityEvent(entity), oldWorldLayer(oldWorldLayer) {}
    };
}

#endif //PAXENGINE3_ENTITYDESPAWNEDEVENT_H
