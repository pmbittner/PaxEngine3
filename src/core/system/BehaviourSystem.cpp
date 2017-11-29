//
// Created by Paul on 05.06.2017.
//

#include "../../../include/core/system/BehaviourSystem.h"
#include "../../../include/core/Engine.h"

namespace PAX {
    void BehaviourSystem::update() {
        for (Entity *e : getEntities()) {
            for (Behaviour *b : e->get<Behaviour>())
                b->update();
        }
    }
}