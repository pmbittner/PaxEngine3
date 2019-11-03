//
// Created by Paul on 03.11.2019.
//

#include "paxcore/world/WorldLayerEvent.h"

namespace PAX {
    WorldLayerEvent::WorldLayerEvent(PAX::World *world, PAX::WorldLayer *worldLayer) : world(world), worldLayer(worldLayer) {}
    WorldLayerAddedEvent::WorldLayerAddedEvent(PAX::World *world, PAX::WorldLayer *worldLayer) : WorldLayerEvent(world, worldLayer) {}
    WorldLayerRemovedEvent::WorldLayerRemovedEvent(PAX::World *world, PAX::WorldLayer *worldLayer) : WorldLayerEvent(world, worldLayer) {}
}