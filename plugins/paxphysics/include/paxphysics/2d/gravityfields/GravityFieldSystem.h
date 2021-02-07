//
// Created by Paul Bittner on 07.02.2021.
//

#ifndef MESHFOLD_GRAVITYFIELDSYSTEM_H
#define MESHFOLD_GRAVITYFIELDSYSTEM_H

#include "paxcore/system/GameSystem.h"
#include "paxcore/system/gameentity/GameEntityPropertyPool.h"
#include "GravityFieldSensitive.h"

namespace PAX::Physics {
    class GravityFieldSystem : public GameSystem {
        GameEntityPropertyPool<GravityFieldSensitive> sensitives;

    public:
        void update(UpdateOptions & options) override;
    };
}

#endif //MESHFOLD_GRAVITYFIELDSYSTEM_H
