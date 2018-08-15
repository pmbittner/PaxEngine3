//
// Created by Paul on 21.01.2018.
//

#include "physics/include/box2d/Box2DRigidBody.h"
#include "../include/box2d/Box2DUtils.h"

namespace PAX {
    namespace Physics {
        namespace Box2D {
            RigidBody::RigidBody(const b2BodyDef &bodyDef) : PAX::Physics::RigidBody(), _bodyDef(bodyDef) {

            }

            void RigidBody::attached(Entity *entity) {
                PAX::Physics::RigidBody::attached(entity);
            }

            void RigidBody::createFor(b2World &world) {
                _bodyDef.position = toBox2D(getOwner()->getTransform().position2D());
                _body = world.CreateBody(&_bodyDef);
                _body->CreateFixture(&_fixtureDef);

                b2FixtureDef fd;
                b2PolygonShape s;
                s.SetAsBox(50.0f, 10.0f);
                fd.shape = &s;
                _fixture = _body->CreateFixture(&fd);
            }
        }
    }
}