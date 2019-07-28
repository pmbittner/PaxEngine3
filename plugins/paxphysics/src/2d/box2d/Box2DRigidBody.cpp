//
// Created by Paul on 21.01.2018.
//

#include <Box2D/Box2D.h>

#include "paxphysics/2d/box2d/Box2DRigidBody.h"
#include "paxphysics/2d/box2d/Box2DUtils.h"

namespace PAX::Physics {
    PAX_PROPERTY_SOURCE(PAX::Physics::Box2DRigidBody, PAX_PROPERTY_IS_CONCRETE)

    Box2DRigidBody * Box2DRigidBody::createFromProvider(ContentProvider & provider) {
        // TODO: FIXME
        return new Box2DRigidBody(b2BodyDef());//provider.require<b2BodyDef>("b2BodyDef"));
    }

    void Box2DRigidBody::initializeFromProvider(ContentProvider & provider) {
        Super::initializeFromProvider(provider);
    }

    Box2DRigidBody::Box2DRigidBody(const b2BodyDef &bodyDef) : RigidBody2D(), _bodyDef(bodyDef) {

    }

    void Box2DRigidBody::attached(Entity &entity) {
        PAX::Physics::RigidBody2D::attached(entity);
    }

    void Box2DRigidBody::createFor(b2World &world) {
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