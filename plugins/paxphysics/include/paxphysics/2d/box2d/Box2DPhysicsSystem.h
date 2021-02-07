//
// Created by Paul on 21.01.2018.
//

#ifndef PAXENGINE3_BOX2DPHYSICSSYSTEM_H
#define PAXENGINE3_BOX2DPHYSICSSYSTEM_H

#include "paxcore/system/GameSystem.h"
#include "polypropylene/memory/PropertyPool.h"
#include "Box2DHitbox.h"
#include "Box2DRigidBody.h"

namespace PAX::Physics {
    class Box2DPhysicsSystem : public GameSystem {
        PropertyPool<PAX::Physics::Box2DHitbox> hitboxes;
        PropertyPool<PAX::Physics::Box2DRigidBody> rigidBodies;

        bool showingHitboxes = false;

    public:
        explicit Box2DPhysicsSystem();

        void initialize(Game * game) override;
        void update(UpdateOptions & options) override;

        void toggleShowHitboxes();
    };
}

#endif //PAXENGINE3_BOX2DPHYSICSSYSTEM_H
