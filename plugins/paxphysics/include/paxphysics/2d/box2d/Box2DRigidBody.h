//
// Created by Paul on 21.01.2018.
//

#ifndef PAXENGINE3_BOX2DPHYSICS_H
#define PAXENGINE3_BOX2DPHYSICS_H

#include <paxphysics/2d/RigidBody2D.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>

namespace PAX::Physics {
        class Box2DRigidBody : public PAX::Physics::RigidBody2D {
            PAX_PROPERTY(PAX::Physics::Box2DRigidBody, PAX_PROPERTY_IS_CONCRETE)
            PAX_PROPERTY_DERIVES(PAX::Physics::RigidBody2D)
            PAX_PROPERTY_IS_MULTIPLE

            b2BodyDef _bodyDef;
            b2FixtureDef _fixtureDef;

            b2Body *_body;
            b2Fixture *_fixture;

        public:
            explicit Box2DRigidBody(const b2BodyDef &bodyDef);

            void createFor(b2World &world);

            void attached(GameEntity &entity) override;
        };
    }

#endif //PAXENGINE3_BOX2DPHYSICS_H
