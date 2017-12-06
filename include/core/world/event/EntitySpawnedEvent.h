//
// Created by Paul on 08.05.2017.
//

#ifndef PAXENGINE3_ENTITYSPAWNEDEVENT_H
#define PAXENGINE3_ENTITYSPAWNEDEVENT_H

#include "../../entity/Entity.h"
#include "../../entity/event/EntityEvent.h"

namespace PAX {
    struct EntitySpawnedEvent : public EntityEvent {
        EntitySpawnedEvent(Entity *entity) : EntityEvent(entity) {}
    };
}

#endif //PAXENGINE3_ENTITYSPAWNEDEVENT_H
