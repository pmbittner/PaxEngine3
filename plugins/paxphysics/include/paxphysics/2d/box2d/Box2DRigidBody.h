//
// Created by Paul on 21.01.2018.
//

#ifndef PAXENGINE3_BOX2DPHYSICS_H
#define PAXENGINE3_BOX2DPHYSICS_H

#include <paxphysics/2d/RigidBody2D.h>
#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
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

        b2Body * getBody() const;
    };
}

#endif //PAXENGINE3_BOX2DPHYSICS_H
