//
// Created by Paul on 24.03.2019.
//

#include <paxcore/system/world/WorldBehaviourSystem.h>
#include <paxcore/world/property/WorldBehaviour.h>

namespace PAX {
    void WorldBehaviourSystem::update(UpdateOptions & options) {
        if (World * w = GameSystem::getGame()->getActiveWorld()) {
            for (WorldBehaviour * b : w->get<WorldBehaviour>()) {
                b->update(options);
            }
        }
    }
}