//
// Created by Paul on 05.06.2017.
//

#ifndef PAXENGINE3_BEHAVIOURSYSTEM_H
#define PAXENGINE3_BEHAVIOURSYSTEM_H

#include "EntityComponentSystem.h"
#include "../entity/component/Behaviour.h"

namespace PAX {
    class BehaviourSystem : public EntityComponentSystem<Behaviour> {
    public:
        virtual void update() override;
    };
}

#endif //PAXENGINE3_BEHAVIOURSYSTEM_H
