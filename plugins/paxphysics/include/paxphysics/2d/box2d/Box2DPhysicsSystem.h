//
// Created by Paul on 21.01.2018.
//

#ifndef PAXENGINE3_BOX2DPHYSICSSYSTEM_H
#define PAXENGINE3_BOX2DPHYSICSSYSTEM_H

#include "paxphysics/2d/PhysicsSystem2D.h"
#include "paxcore/system/gameentity/GameEntityPropertyPool.h"
#include "Box2DHitbox.h"
#include "Box2DRigidBody.h"

namespace PAX::Physics {
    class Box2DPhysicsSystem : public PhysicsSystem2D {
        using Super = PhysicsSystem2D;

        GameEntityPropertyPool<PAX::Physics::Box2DHitbox> hitboxes;
//        PropertyPool<PAX::Physics::Box2DRigidBody> rigidBodies;
        bool showingHitboxes = false;

    public:
        explicit Box2DPhysicsSystem();

        void initialize(Game * game) override;
        void update(UpdateOptions & options) override;

        void toggleShowHitboxes() override;
    };
}

#endif //PAXENGINE3_BOX2DPHYSICSSYSTEM_H
