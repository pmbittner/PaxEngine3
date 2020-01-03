//
// Created by bittner on 9/27/17.
//

#ifndef PAXENGINE3_WORLDEVENT_H
#define PAXENGINE3_WORLDEVENT_H

#include "polypropylene/event/Event.h"
#include "../World.h"

namespace PAX {
    struct WorldEvent : public Event {
        World * world;

        WorldEvent(World *world) : world(world) {}
    };
}

#endif //PAXENGINE3_WORLDEVENT_H
