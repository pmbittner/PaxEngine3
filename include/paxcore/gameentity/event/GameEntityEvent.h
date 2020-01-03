//
// Created by Paul on 08.05.2017.
//

#ifndef PAXENGINE3_ENTITYEVENT_H
#define PAXENGINE3_ENTITYEVENT_H

#include "polypropylene/event/Event.h"

namespace PAX {
    class GameEntity;

    struct GameEntityEvent : public Event {
    public:
        GameEntity* entity = nullptr;
        explicit GameEntityEvent(GameEntity *entity) : entity(entity) {}
    };
}

#endif //PAXENGINE3_ENTITYEVENT_H
