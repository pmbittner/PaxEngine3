//
// Created by Paul on 24.03.2019.
//

#ifndef PAXENGINE3_WORLDBEHAVIOURSYSTEM_H
#define PAXENGINE3_WORLDBEHAVIOURSYSTEM_H

#include <paxcore/system/GameSystem.h>

namespace PAX {
    class WorldBehaviourSystem : public GameSystem {
    public:
        void update(UpdateOptions & options) override;
    };
}

#endif //PAXENGINE3_WORLDBEHAVIOURSYSTEM_H
