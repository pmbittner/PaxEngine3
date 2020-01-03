//
// Created by Paul on 05.06.2017.
//

#include <paxcore/system/gameentity/BehaviourSystem.h>
#include <paxcore/Engine.h>

namespace PAX {
    void BehaviourSystem::update(UpdateOptions & options) {
        for (WorldLayer * worldLayer : getWorldLayers()) {
            for (GameEntity * e : getEntities(worldLayer)) {
                for (const auto &b : e->get<Behaviour>()) {
                    b->update(options);
                }
            }
        }
    }
}