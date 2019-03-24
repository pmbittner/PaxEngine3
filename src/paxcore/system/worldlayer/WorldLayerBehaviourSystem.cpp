//
// Created by Paul on 24.03.2019.
//

#include <paxcore/system/worldlayer/WorldLayerBehaviourSystem.h>

namespace PAX {
    void WorldLayerBehaviourSystem::update() {
        for (WorldLayer * w : getWorldLayers()) {
            for (WorldLayerBehaviour * b : w->get<WorldLayerBehaviour>()) {
                b->update();
            }
        }
    }
}