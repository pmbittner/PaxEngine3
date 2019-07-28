//
// Created by Paul on 21.01.2018.
//

#ifndef PAXENGINE3_BOX2DPHYSICSSYSTEM_H
#define PAXENGINE3_BOX2DPHYSICSSYSTEM_H

#include <paxcore/system/entity/EntityPropertySystem.h>

#include "Box2DHitbox.h"

namespace PAX::Physics {
    class Box2DPhysicsSystem : public EntityPropertySystem<PAX::Physics::Box2DHitbox> {
    public:
        Box2DPhysicsSystem();

        void initialize(Game *game) override;
        void update(UpdateOptions & options) override;
    };
}

#endif //PAXENGINE3_BOX2DPHYSICSSYSTEM_H
