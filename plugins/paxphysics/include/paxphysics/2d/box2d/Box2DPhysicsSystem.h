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

        float pixelsPerMeter = 1;
        float metersPerPixel = 1;

        bool showingHitboxes = false;

    public:
        explicit Box2DPhysicsSystem(float pixelsPerMeter);

        void initialize(Game *game) override;
        void update(UpdateOptions & options) override;

        void setPixelsPerMeter(float pixelsPerMeter);
        float getMetersPerPixel();
        float getPixelsPerMeter();

        void toggleShowHitboxes();
    };
}

#endif //PAXENGINE3_BOX2DPHYSICSSYSTEM_H
