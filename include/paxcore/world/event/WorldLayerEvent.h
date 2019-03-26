//
// Created by Paul on 23.03.2019.
//

#ifndef PAXENGINE3_WORLDLAYEREVENT_H
#define PAXENGINE3_WORLDLAYEREVENT_H

#include <paxutil/event/Event.h>
#include <paxcore/world/WorldLayer.h>

namespace PAX {
    struct WorldLayerEvent : public Event {
        World & world;
        WorldLayer & worldLayer;

        WorldLayerEvent(World & world, WorldLayer & worldLayer) : world(world), worldLayer(worldLayer) {}
    };

    struct WorldLayerAddedEvent : public WorldLayerEvent {
        WorldLayerAddedEvent(World & world, WorldLayer & worldLayer) : WorldLayerEvent(world, worldLayer) {}
    };

    struct WorldLayerRemovedEvent : public WorldLayerEvent {
        WorldLayerRemovedEvent(World & world, WorldLayer & worldLayer) : WorldLayerEvent(world, worldLayer) {}
    };
}

#endif //PAXENGINE3_WORLDLAYEREVENT_H
