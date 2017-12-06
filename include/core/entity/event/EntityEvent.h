//
// Created by Paul on 08.05.2017.
//

#ifndef PAXENGINE3_ENTITYEVENT_H
#define PAXENGINE3_ENTITYEVENT_H

#include "../Entity.h"
#include "../../event/Event.h"

namespace PAX {
    struct EntityEvent : public Event {
    public:
        Entity* entity;
        EntityEvent(Entity *entity) : entity(entity) {}
    };
}

#endif //PAXENGINE3_ENTITYEVENT_H
