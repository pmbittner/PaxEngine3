//
// Created by Paul on 28.09.2018.
//

#ifndef PAXENGINE3_WORLDLAYEREVENT_H
#define PAXENGINE3_WORLDLAYEREVENT_H

#include "paxutil/event/Event.h"

namespace PAX {
    class WorldLayer;

    struct WorldLayerEvent : public Event {
    public:
        WorldLayer* worldLayer = nullptr;
        explicit WorldLayerEvent(WorldLayer *worldLayer) : worldLayer(worldLayer) {}
    };
}

#endif //PAXENGINE3_WORLDLAYEREVENT_H
