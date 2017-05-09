//
// Created by Paul on 08.05.2017.
//

#ifndef PAXENGINE3_ENTITYSPAWNEDEVENT_H
#define PAXENGINE3_ENTITYSPAWNEDEVENT_H

#include "../../entity/Entity.h"
#include "../../entity/EntityEvent.h"

namespace PAX {
    class EntitySpawnedEvent : public EntityEvent {
    public:
        EntitySpawnedEvent(Entity *entity) : EntityEvent(entity) {}
    };
}

#endif //PAXENGINE3_ENTITYSPAWNEDEVENT_H
