//
// Created by Paul on 28.07.2019.
//

#include <paxcore/world/WorldLayer.h>
#include <paxphysics/2d/box2d/Box2DHitbox.h>
#include <paxphysics/2d/box2d/Box2DWorld.h>
#include <Box2D/Dynamics/b2Body.h>
#include <paxphysics/2d/box2d/Box2DUtils.h>

#include <paxcore/Engine.h>
#include <paxcore/Game.h>
#include <paxphysics/2d/box2d/Box2DPhysicsSystem.h>

namespace PAX::Physics {
    PAX_PROPERTY_INIT(PAX::Physics::Box2DHitbox, PAX_PROPERTY_IS_CONCRETE)

    Box2DHitbox::This * Box2DHitbox::createFromProvider(PAX::ContentProvider & p) {
        return new Box2DHitbox();
    }

    void Box2DHitbox::initializeFromProvider(PAX::ContentProvider & p) {
        Super::initializeFromProvider(p);
    }

    Box2DHitbox::Box2DHitbox() : Hitbox2D() {

    }

    Box2DHitbox::~Box2DHitbox() = default;

    void Box2DHitbox::uploadToBox2D(Box2DWorld & box2DWorld) {
        GameEntity * owner = getOwner();
        if (!owner) {
            return;
        }

        b2World & world = box2DWorld.getb2World();

        // Convert shape to box2d shape
        if (body) {
            for (b2Fixture * f : fixtures) {
                body->DestroyFixture(f);
            }

            fixtures.clear();
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
                fixtures.push_back(body->CreateFixture(&fixtureDef));
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

    void Box2DHitbox::activated() {
        WorldLayer * worldLayer = getOwner()->getWorldLayer();
        if (Box2DWorld * world = worldLayer->get<Box2DWorld>()) {
            uploadToBox2D(*world);
        }
    }

    void Box2DHitbox::deactivated() {
        PAX_NOT_IMPLEMENTED();
    }

    // TODO: Consider scale of engine to box2d

    void Box2DHitbox::synchronizeBox2D(float metersPerPixel) {
        if (body) {
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