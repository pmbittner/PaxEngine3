//
// Created by Paul on 24.03.2019.
//

#ifndef PAXENGINE3_WORLDLAYERBEHAVIOURSYSTEM_H
#define PAXENGINE3_WORLDLAYERBEHAVIOURSYSTEM_H

#include <paxcore/world/property/WorldLayerBehaviour.h>
#include "WorldLayerPropertySystem.h"

namespace PAX {
    class WorldLayerBehaviourSystem : public WorldLayerPropertySystem<WorldLayerBehaviour> {
    public:
        void update(UpdateOptions & options) override;
    };
}

#endif //PAXENGINE3_WORLDLAYERBEHAVIOURSYSTEM_H
