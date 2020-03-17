//
// Created by Paul on 24.03.2019.
//

#ifndef PAXENGINE3_WORLDBEHAVIOURSYSTEM_H
#define PAXENGINE3_WORLDBEHAVIOURSYSTEM_H

#include <paxcore/world/property/WorldBehaviour.h>
#include <paxcore/system/WorldSystem.h>

namespace PAX {
    class WorldBehaviourSystem : public WorldSystem {
    public:
        void update(UpdateOptions & options) override;
    };
}

#endif //PAXENGINE3_WORLDBEHAVIOURSYSTEM_H
