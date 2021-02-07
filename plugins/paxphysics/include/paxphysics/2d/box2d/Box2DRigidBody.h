//
// Created by Paul on 21.01.2018.
//

#ifndef PAXENGINE3_BOX2DPHYSICS_H
#define PAXENGINE3_BOX2DPHYSICS_H

#include <paxphysics/2d/RigidBody2D.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include "Box2DHitbox.h"

namespace PAX::Physics {
    class Box2DRigidBody : public RigidBody2D {
        PAX_PROPERTY(PAX::Physics::Box2DRigidBody, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(PAX::Physics::RigidBody2D)
        PAX_PROPERTY_IS_MULTIPLE

        PAX_PROPERTY_DEPENDS_ON(Box2DHitbox) // because a rigidbody without hitboxes has no purpose

        friend class Box2DWorld;
        b2Body * body = nullptr;

    public:
        Box2DRigidBody();
        ~Box2DRigidBody() override;

        void attached(GameEntity & entity) override;
        void detached(GameEntity & entity) override;

        void setFixedRotation(bool fixedRotation) override;
    };
}

#endif //PAXENGINE3_BOX2DPHYSICS_H
