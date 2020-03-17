//
// Created by Paul on 24.03.2019.
//

#include <paxcore/system/world/WorldBehaviourSystem.h>

namespace PAX {
    void WorldBehaviourSystem::update(UpdateOptions & options) {
        if (World * w = WorldSystem::getActiveWorld()) {
            for (WorldBehaviour * b : w->get<WorldBehaviour>()) {
                b->update(options);
            }
        }
    }
}