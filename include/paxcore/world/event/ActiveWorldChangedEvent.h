//
// Created by bittner on 9/27/17.
//

#ifndef PAXENGINE3_ACTIVEWORLDCHANGEDEVENT_H
#define PAXENGINE3_ACTIVEWORLDCHANGEDEVENT_H

#include "paxutil/event/Event.h"
#include "../World.h"

namespace PAX {
    struct ActiveWorldChangedEvent : public Event {
        World *oldWorld, *newWorld;

        ActiveWorldChangedEvent(World* oldWorld, World* newWorld) : oldWorld(oldWorld), newWorld(newWorld) {

        }
    };
}



#endif //PAXENGINE3_ACTIVEWORLDCHANGEDEVENT_H
