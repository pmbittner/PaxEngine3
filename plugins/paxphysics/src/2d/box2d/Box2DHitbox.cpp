//
// Created by Paul on 28.07.2019.
//

#include <paxphysics/2d/box2d/Box2DHitbox.h>
#include <paxphysics/2d/box2d/Box2DWorld.h>
#include <Box2D/Dynamics/b2Body.h>
#include <paxphysics/2d/box2d/Box2DUtils.h>

#include <paxcore/Engine.h>
#include <paxcore/Game.h>
#include <paxphysics/2d/box2d/Box2DPhysicsSystem.h>

namespace PAX::Physics {
    PAX_PROPERTY_IMPL(PAX::Physics::Box2DHitbox)

    Box2DHitbox::Box2DHitbox() : Hitbox2D() {

    }

    Box2DHitbox::~Box2DHitbox() = default;

    void Box2DHitbox::uploadToBox2D(Box2DWorld & box2DWorld) {
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
            for (const Fixture2D &f : getFixtures()) {
                b2Shape *bshape = toBox2D(f.shape.get(), b2PhysicsSystem->getMetersPerPixel());

                b2FixtureDef fixtureDef;
                fixtureDef.shape = bshape;
                fixtureDef.density = f.material->density;
                fixtureDef.friction = f.material->friction;
                fixtureDef.restitution = f.material->elasticity;
                b2Fixtures.push_back(body->CreateFixture(&fixtureDef));
                /// "Box2D does not keep a reference to the shape. It clones the data into a new b2Shape object."
                delete bshape;
            }
        }
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

    void Box2DHitbox::setFixedRotation(bool fixedRotation) {
        Super::setFixedRotation(fixedRotation);
        if (body) {
            body->SetFixedRotation(fixedRotation);
        }
    }

    void Box2DHitbox::spawned() {
        World * world = getOwner()->getWorld();
        if (Box2DWorld * b2world = world->get<Box2DWorld>()) {
            uploadToBox2D(*b2world);
        }
    }

    void Box2DHitbox::despawned() {
        PAX_NOT_IMPLEMENTED();
    }

    // TODO: Consider scale of engine to box2d

    void Box2DHitbox::synchronizeBox2D(float metersPerPixel) {
        if (body) {
//            PAX_LOG(Log::Level::Info, "");
            Transformation & t = getOwner()->getTransformation();
            body->SetTransform(toBox2D(metersPerPixel * t.position2D()), t.getRotation2DInRadians());
            // TODO: update velocity
        }
    }

    void Box2DHitbox::synchronizePaxEngine(float pixelsPerMeter) {
        if (body) {
            Transformation & t = getOwner()->getTransformation();
            t.position2D() = pixelsPerMeter * toGLM(body->GetPosition());
            t.setRotation2DInRadians(body->GetAngle());
            // TODO: update velocity
        }
    }
}