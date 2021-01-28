//
// Created by Paul on 21.01.2018.
//

#ifndef PAXENGINE3_BOX2DPHYSICS_H
#define PAXENGINE3_BOX2DPHYSICS_H

#include <paxphysics/2d/RigidBody2D.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include "Box2DWorld.h"

namespace PAX::Physics {
    class Box2DRigidBody : public PAX::Physics::RigidBody2D {
        PAX_PROPERTY(PAX::Physics::Box2DRigidBody, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(PAX::Physics::RigidBody2D)
        PAX_PROPERTY_IS_MULTIPLE

        b2Body * body = nullptr;
        std::vector<b2Fixture *> b2Fixtures;

        void uploadToBox2D(Box2DWorld & box2DWorld);

    public:
        Box2DRigidBody();
        ~Box2DRigidBody() override;

        void spawned() override;
        void despawned() override;

        void synchronizeBox2D(float metersPerPixel);
        void synchronizePaxEngine(float pixelsPerMeter);

        void setFixedRotation(bool fixedRotation) override;
    };
}

#endif //PAXENGINE3_BOX2DPHYSICS_H
