//
// Created by Paul on 05.06.2017.
//

#ifndef PAXENGINE3_BEHAVIOURSYSTEM_H
#define PAXENGINE3_BEHAVIOURSYSTEM_H

#include "EntityPropertySystem.h"
#include <paxcore/entity/property/Behaviour.h>

namespace PAX {
    class BehaviourSystem : public EntityPropertySystem<Behaviour> {
    public:
        void update() override;
    };
}

#endif //PAXENGINE3_BEHAVIOURSYSTEM_H
