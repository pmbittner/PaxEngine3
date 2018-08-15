//
// Created by Paul on 21.01.2018.
//

#include "../include/box2d/Box2DPhysics.h"
#include "../include/box2d/Box2DUtils.h"

namespace PAX {
    namespace Box2D {
        Physics::Physics(const b2BodyDef& bodyDef) : PAX::Physics(), _bodyDef(bodyDef) {

        }

        void Physics::attached(Entity *entity) {
            PAX::Physics::attached(entity);
        }

        void Physics::createFor(b2World &world) {
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