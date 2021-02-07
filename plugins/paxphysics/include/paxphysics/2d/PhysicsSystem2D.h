//
// Created by Paul Bittner on 07.02.2021.
//

#ifndef MESHFOLD_PHYSICSSYSTEM2D_H
#define MESHFOLD_PHYSICSSYSTEM2D_H

#include "paxcore/system/GameSystem.h"

namespace PAX::Physics {
    class PhysicsSystem2D : public GameSystem {
    public:
        virtual void toggleShowHitboxes() = 0;
    };
}

#endif //MESHFOLD_PHYSICSSYSTEM2D_H
