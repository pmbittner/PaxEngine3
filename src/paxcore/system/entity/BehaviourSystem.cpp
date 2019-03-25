//
// Created by Paul on 05.06.2017.
//

#include <paxcore/system/entity/BehaviourSystem.h>
#include <paxcore/Engine.h>

namespace PAX {
    void BehaviourSystem::update() {
        for (WorldLayer * worldLayer : getWorldLayers()) {
            for (Entity * e : getEntities(worldLayer)) {
                for (const auto &b : e->get<Behaviour>()) {
                    b->update();
                }
            }
        }
    }
}