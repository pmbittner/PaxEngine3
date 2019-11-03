//
// Created by Paul on 03.11.2019.
//

#ifndef PAXENGINE3_WORLDLAYEREVENT_H
#define PAXENGINE3_WORLDLAYEREVENT_H

#include "WorldLayer.h"

namespace PAX {
    struct WorldLayerEvent : public Event {
        World * world;
        WorldLayer * worldLayer;

        WorldLayerEvent(World * world, WorldLayer * worldLayer);
    };

    struct WorldLayerAddedEvent : public WorldLayerEvent {
        WorldLayerAddedEvent(World * world, WorldLayer * worldLayer);
    };

    struct WorldLayerRemovedEvent : public WorldLayerEvent {
        WorldLayerRemovedEvent(World * world, WorldLayer * worldLayer);
    };
}

#endif //PAXENGINE3_WORLDLAYEREVENT_H
