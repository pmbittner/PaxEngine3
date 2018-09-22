//
// Created by Paul on 05.06.2017.
//

#include <paxcore/system/BehaviourSystem.h>
#include <paxcore/Engine.h>

namespace PAX {
    void BehaviourSystem::update() {
        for (Entity *e : getEntities()) {
            for (const auto & b : e->get<Behaviour>())
                b->update();
        }
    }
}