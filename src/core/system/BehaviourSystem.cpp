//
// Created by Paul on 05.06.2017.
//

#include "../../../include/core/system/BehaviourSystem.h"
#include "../../../include/core/Engine.h"

namespace PAX {
    void BehaviourSystem::update() {
        for (Entity *e : getEntities()) {
            const std::vector<Behaviour*> *v = e->get<Behaviour>();
            for (Behaviour *b : *v) {
                b->update();
            }
        }
    }
}