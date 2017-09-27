//
// Created by bittner on 9/27/17.
//

#ifndef PAXENGINE3_ACTIVEWORLDCHANGEDEVENT_H
#define PAXENGINE3_ACTIVEWORLDCHANGEDEVENT_H

#include "../../event/Event.h"
#include "../World.h"

namespace PAX {
    class ActiveWorldChangedEvent : public Event {
    public:
        World *oldWorld, *newWorld;

        ActiveWorldChangedEvent(World* oldWorld, World* newWorld) : oldWorld(oldWorld), newWorld(newWorld) {

        }
    };
}



#endif //PAXENGINE3_ACTIVEWORLDCHANGEDEVENT_H
