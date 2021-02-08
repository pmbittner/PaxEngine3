//
// Created by Paul Bittner on 07.02.2021.
//

#ifndef MESHFOLD_GRAVITYFIELDSYSTEM_H
#define MESHFOLD_GRAVITYFIELDSYSTEM_H

#include "paxcore/system/gameentity/GameEntityPropertySystem.h"
#include "paxcore/system/gameentity/GameEntityPropertyPool.h"
#include "GravityFieldSensitive.h"
#include "GravityField.h"

namespace PAX::Physics {
    class GravityFieldSystem : public GameEntityPropertySystem<GravityField> {
        GameEntityPropertyPool<GravityFieldSensitive> sensitives;

    public:
        void update(UpdateOptions & options) override;
    };
}

#endif //MESHFOLD_GRAVITYFIELDSYSTEM_H
