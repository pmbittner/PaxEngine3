//
// Created by Paul on 21.01.2018.
//

#include <paxphysics/2d/box2d/Box2DRigidBody.h>
#include <paxphysics/2d/box2d/Box2DHitbox.h>
#include <paxphysics/2d/box2d/Box2DUtils.h>

#include <paxcore/Engine.h>
#include <paxcore/Game.h>
#include <paxphysics/2d/box2d/Box2DPhysicsSystem.h>
#include <paxcore/gameentity/property/behaviours/2d/Movement2D.h>


namespace PAX::Physics {
    PAX_PROPERTY_IMPL(PAX::Physics::Box2DRigidBody)

    Box2DRigidBody::Box2DRigidBody() : RigidBody2D() {}

    Box2DRigidBody::~Box2DRigidBody() = default;

    void Box2DRigidBody::setFixedRotation(bool fixedRotation) {
        Super::setFixedRotation(fixedRotation);
        if (body) {
            body->SetFixedRotation(fixedRotation);
        }
    }

    void Box2DRigidBody::attached(GameEntity &entity) {
        Super::attached(entity);
        if (Movement2D * movement = entity.get<Movement2D>()) {
            movement->deactivate();
        }
    }

    void Box2DRigidBody::detached(GameEntity &entity) {
        Super::detached(entity);
        if (Movement2D * movement = entity.get<Movement2D>()) {
            movement->activate();
        }
    }

    b2Body * Box2DRigidBody::getBody() const {
        return body;
    }
}