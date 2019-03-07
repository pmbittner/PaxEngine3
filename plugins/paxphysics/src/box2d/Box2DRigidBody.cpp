//
// Created by Paul on 21.01.2018.
//

#include "paxphysics/box2d/Box2DRigidBody.h"
#include "paxphysics/box2d/Box2DUtils.h"

namespace PAX {
    namespace Physics {
        namespace Box2D {
            PAX_PROPERTY_SOURCE(PAX::Physics::Box2D::RigidBody, PAX_PROPERTY_IS_CONCRETE)

            RigidBody * RigidBody::createFromProvider(ContentProvider & provider) {
                // TODO: FIXME
                return new RigidBody(b2BodyDef());//provider.require<b2BodyDef>("b2BodyDef"));
            }

            void RigidBody::initializeFromProvider(ContentProvider & provider) {
                Super::initializeFromProvider(provider);
            }

            RigidBody::RigidBody(const b2BodyDef &bodyDef) : PAX::Physics::RigidBody(), _bodyDef(bodyDef) {

            }

            void RigidBody::attached(Entity &entity) {
                PAX::Physics::RigidBody::attached(entity);
            }

            void RigidBody::createFor(b2World &world) {
                _bodyDef.position = toBox2D(getOwner()->getTransformation().position2D());
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