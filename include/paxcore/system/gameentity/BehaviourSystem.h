//
// Created by Paul on 05.06.2017.
//

#ifndef PAXENGINE3_BEHAVIOURSYSTEM_H
#define PAXENGINE3_BEHAVIOURSYSTEM_H

#include "GameEntityPropertySystem.h"
#include <paxcore/gameentity/property/Behaviour.h>

namespace PAX {
    class BehaviourSystem : public GameEntityPropertySystem<Behaviour> {
    public:
        void update(UpdateOptions & options) override;
    };
}

#endif //PAXENGINE3_BEHAVIOURSYSTEM_H
