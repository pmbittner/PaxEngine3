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

    void Box2DRigidBody::uploadToBox2D(Box2DWorld & box2DWorld) {
        GameEntity * owner = getOwner();
        if (!owner) {
            PAX_THROW_RUNTIME_ERROR("");
        }

        b2World & world = box2DWorld.getb2World();

        // Convert shape to box2d shape
        if (body) {
            for (b2Fixture * f : b2Fixtures) {
                body->DestroyFixture(f);
            }

            b2Fixtures.clear();
        } else {
            b2BodyDef bodyDef;
            bodyDef.type = toBox2D(owner->getMotionType());
            bodyDef.fixedRotation = hasFixedRotation();
            body = world.CreateBody(&bodyDef);
        }

        if (Box2DPhysicsSystem * b2PhysicsSystem = Engine::Instance().getGame()->getSystem<Box2DPhysicsSystem>()) {
            const std::vector<Box2DHitbox*> & hitboxes = owner->get<Box2DHitbox>();
            for (Box2DHitbox * hitbox : hitboxes) {
                const Shape2D & shape = hitbox->getShape();
                const std::shared_ptr<PhysicsMaterial> & material = hitbox->getMaterial();
                b2Shape *bshape = toBox2D(&shape, b2PhysicsSystem->getMetersPerPixel());

                b2FixtureDef fixtureDef;
                fixtureDef.shape = bshape;
                fixtureDef.density = material->density;
                fixtureDef.friction = material->friction;
                fixtureDef.restitution = material->elasticity;
                b2Fixtures.push_back(body->CreateFixture(&fixtureDef));

                /// "Box2D does not keep a reference to the shape. It clones the data into a new b2Shape object."
                delete bshape;
            }
        }

        body->ResetMassData();
    }

    // TODO: Change this to onFixtureChanged and update a b2Fixture, if the correpsonding PAX::Physics::Fixture was changed.
    /*
    void Box2DHitbox::onShapeChanged() {
        if (GameEntity * owner = getOwner()) {
            if (owner->isActive()) {
                if (Box2DWorld *world = owner->getWorldLayer()->get<Box2DWorld>()) {
                    uploadShapeToBox2D(*world);
                }
            }
        }
    }
     */

    void Box2DRigidBody::setFixedRotation(bool fixedRotation) {
        Super::setFixedRotation(fixedRotation);
        if (body) {
            body->SetFixedRotation(fixedRotation);
        }
    }

    void Box2DRigidBody::spawned() {
        World * world = getOwner()->getWorld();
        if (Box2DWorld * b2world = world->get<Box2DWorld>()) {
            uploadToBox2D(*b2world);
        }
    }

    void Box2DRigidBody::despawned() {
        PAX_NOT_IMPLEMENTED();
    }

    // TODO: Consider scale of engine to box2d

    void Box2DRigidBody::synchronizeBox2D(float metersPerPixel) {
        GameEntity * owner = getOwner();
        if (body && owner) {
            Transformation & t = owner->getTransformation();
            body->SetTransform(toBox2D(metersPerPixel * t.position2D()), t.getRotation2DInRadians());

            if (Movement2D * v = owner->get<Movement2D>()) {
                body->SetAngularVelocity(Math::toRadians(v->angularVelocityInDegrees));
                body->SetLinearVelocity(toBox2D(metersPerPixel * v->velocity));
            }
        }
    }

    void Box2DRigidBody::synchronizePaxEngine(float pixelsPerMeter) {
        GameEntity * owner = getOwner();
        if (body && owner) {
            Transformation & paxTransform = owner->getTransformation();
            const b2Transform & box2DTransform = body->GetTransform();
            paxTransform.position2D() = pixelsPerMeter * toGLM(box2DTransform.p);
            paxTransform.setRotation2DInRadians(box2DTransform.q.GetAngle());

            if (Movement2D * v = owner->get<Movement2D>()) {
                v->velocity = pixelsPerMeter * toGLM(body->GetLinearVelocity());
                v->angularVelocityInDegrees = Math::toDegrees(body->GetAngularVelocity());
            }
        }
    }
}