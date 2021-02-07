//
// Created by Paul on 23.03.2019.
//

#include <paxphysics/2d/box2d/Box2DWorld.h>
#include <paxphysics/2d/box2d/Box2DUtils.h>
#include <paxphysics/2d/box2d/Box2DPhysicsSystem.h>
#include <paxcore/Engine.h>
#include <paxcore/gameentity/property/behaviours/2d/Movement2D.h>

namespace PAX::Physics {
    PAX_PROPERTY_IMPL(PAX::Physics::Box2DWorld)

    Box2DWorld::Box2DWorld() : Box2DWorld(glm::vec2(0)) {}

    Box2DWorld::Box2DWorld(const glm::vec2 & gravity) : PhysicsWorld2D(gravity), box2dWorld(toBox2D(gravity)) {
        box2dWorld.SetAllowSleeping(false);
    }

    void Box2DWorld::setGravity(const glm::vec2 &gravity) {
        Super::setGravity(gravity);
        box2dWorld.SetGravity(toBox2D(gravity));
    }

    b2World& Box2DWorld::getb2World() {
        return box2dWorld;
    }

    void Box2DWorld::step(PAX::UpdateOptions &options) {
        box2dWorld.Step(options.dt, velocityIterations, positionIterations);
    }

    void Box2DWorld::created() {
        // update Box2D
        Super::created();
        setGravity(getGravity());
    }

    // TODO: Consider scale of engine to box2d

    void Box2DWorld::synchronizeBox2D(float metersPerPixel) {
        GameEntity * entity = nullptr;
        b2Body * body = nullptr;
        for (auto & entry : bodies) {
            entity = entry.first;
            body = entry.second;
            Transformation &t = entity->getTransformation();
            body->SetTransform(toBox2D(metersPerPixel * t.position2D()), t.getRotation2DInRadians());

            if (Movement2D * v = entity->get<Movement2D>()) {
                body->SetAngularVelocity(Math::toRadians(v->angularVelocityInDegrees));
                body->SetLinearVelocity(toBox2D(metersPerPixel * v->velocity));
            }
        }
    }

    void Box2DWorld::synchronizePaxEngine(float pixelsPerMeter) {
        GameEntity * entity = nullptr;
        b2Body * body = nullptr;
        for (auto & entry : bodies) {
            entity = entry.first;
            body = entry.second;
            Transformation & paxTransform = entity->getTransformation();
            const b2Transform & box2DTransform = body->GetTransform();
            paxTransform.position2D() = pixelsPerMeter * toGLM(box2DTransform.p);
            paxTransform.setRotation2DInRadians(box2DTransform.q.GetAngle());

            if (Movement2D * v = entity->get<Movement2D>()) {
                v->velocity = pixelsPerMeter * toGLM(body->GetLinearVelocity());
                v->angularVelocityInDegrees = Math::toDegrees(body->GetAngularVelocity());
            }
        }
    }

    void Box2DWorld::spawnInBox2D(GameEntity &entity) {
//        PAX_LOG(Log::Level::Info, "");
        Box2DPhysicsSystem * b2PhysicsSystem = Engine::Instance().getGame()->getSystem<Box2DPhysicsSystem>();
        if (!b2PhysicsSystem) {
            PAX_LOG(Log::Level::Warn,
                    "Trying to spawn entity in Box2D but there is not Box2DPhysicsSystem registered in the Game");
            return;
        }

        Box2DRigidBody * rigidBody = entity.get<Box2DRigidBody>();
        const std::vector<Box2DHitbox*> & hitboxes = entity.get<Box2DHitbox>();
        b2Body * body = bodies[&entity];
        if (body) {
            // This should never happen.
            box2dWorld.DestroyBody(body);
        }

        b2BodyDef bodyDef;
        bodyDef.type = toBox2D(entity.getMotionType());
        if (rigidBody) {
            bodyDef.fixedRotation = rigidBody->hasFixedRotation();
        }
        body = box2dWorld.CreateBody(&bodyDef);
        body->SetUserData(&entity);
        bodies[&entity] = body;

        if (rigidBody) {
            rigidBody->body = body;
        }

        for (Box2DHitbox * hitbox : hitboxes) {
            const Shape2D & shape = hitbox->getShape();
            const std::shared_ptr<PhysicsMaterial> & material = hitbox->getMaterial();
            b2Shape *bshape = toBox2D(&shape, b2PhysicsSystem->getMetersPerPixel());

            b2FixtureDef fixtureDef;
            fixtureDef.shape = bshape;
            fixtureDef.density = material->density;
            fixtureDef.friction = material->friction;
            fixtureDef.restitution = material->elasticity;
            body->CreateFixture(&fixtureDef);

            /// "Box2D does not keep a reference to the shape. It clones the data into a new b2Shape object."
            delete bshape;
        }

        body->ResetMassData();
    }

    void Box2DWorld::despawnInBox2D(GameEntity &entity) {
//        PAX_LOG(Log::Level::Info, "");
        if (b2Body * body = bodies[&entity]) {
            box2dWorld.DestroyBody(body);
            bodies.erase(&entity);
            if (Box2DRigidBody * rigidBody = entity.get<Box2DRigidBody>()) {
                rigidBody->body = nullptr;
            }
        }
    }

    void Box2DWorld::addHitboxToBodyOf(GameEntity &entity, Box2DHitbox &hitbox) {
//        PAX_LOG(Log::Level::Info, "");
    }

    void Box2DWorld::removeHitboxFromBodyOf(GameEntity &entity, Box2DHitbox &hitbox) {
//        PAX_LOG(Log::Level::Info, "");
    }

    void Box2DWorld::turnIntoRigidBody(GameEntity &entity, Box2DRigidBody &rigidBody) {
//        PAX_LOG(Log::Level::Info, "");
    }

    void Box2DWorld::removeRigidBody(GameEntity &entity, Box2DRigidBody &rigidBody) {
//        PAX_LOG(Log::Level::Info, "");
    }

    void Box2DWorld::attached(World &world) {
//        PAX_LOG(Log::Level::Info, "");
        paxWorld = &world;

        EventService & e = world.getEventService();
        using B = Box2DWorld;
        e.add<GameEntitySpawnedEvent, B, &B::onGameEntitySpawned>(this);
        e.add<GameEntityDespawnedEvent, B, &B::onGameEntityDespawned>(this);
        e.add<PropertyAttachedEvent<GameEntity, Box2DHitbox>, B, &B::onHitboxSpawned>(this);
        e.add<PropertyDetachedEvent<GameEntity, Box2DHitbox>, B, &B::onHitboxDespawned>(this);
        e.add<PropertyAttachedEvent<GameEntity, Box2DRigidBody>, B, &B::onRigidBodySpawned>(this);
        e.add<PropertyDetachedEvent<GameEntity, Box2DRigidBody>, B, &B::onRigidBodyDespawned>(this);
    }

    void Box2DWorld::detached(World &world) {
//        PAX_LOG(Log::Level::Info, "");
        EventService & e = world.getEventService();
        using B = Box2DWorld;
        e.remove<GameEntitySpawnedEvent, B, &B::onGameEntitySpawned>(this);
        e.remove<GameEntityDespawnedEvent, B, &B::onGameEntityDespawned>(this);
        e.remove<PropertyAttachedEvent<GameEntity, Box2DHitbox>, B, &B::onHitboxSpawned>(this);
        e.remove<PropertyDetachedEvent<GameEntity, Box2DHitbox>, B, &B::onHitboxDespawned>(this);
        e.remove<PropertyAttachedEvent<GameEntity, Box2DRigidBody>, B, &B::onRigidBodySpawned>(this);
        e.remove<PropertyDetachedEvent<GameEntity, Box2DRigidBody>, B, &B::onRigidBodyDespawned>(this);

        paxWorld = nullptr;
    }

    void Box2DWorld::onGameEntitySpawned(GameEntitySpawnedEvent &e) {
//        PAX_LOG(Log::Level::Info, "");
        if (e.entity->has<Box2DHitbox>()) {
            spawnInBox2D(*e.entity);
        }
    }

    void Box2DWorld::onGameEntityDespawned(GameEntityDespawnedEvent &e) {
//        PAX_LOG(Log::Level::Info, "");
        if (e.entity->has<Box2DHitbox>()) {
            despawnInBox2D(*e.entity);
        }
    }

    void Box2DWorld::onHitboxSpawned(PropertyAttachedEvent<GameEntity, Box2DHitbox> &e) {
//        PAX_LOG(Log::Level::Info, "");
        GameEntity * entity = e.entity;
        auto it = bodies.find(entity);
        if (it == bodies.end()) {
            spawnInBox2D(*entity);
        } else {
            addHitboxToBodyOf(*entity, *e.property);
        }
    }

    void Box2DWorld::onHitboxDespawned(PropertyDetachedEvent<GameEntity, Box2DHitbox> &e) {
//        PAX_LOG(Log::Level::Info, "");
        GameEntity * entity = e.entity;
        auto it = bodies.find(entity);
        if (it == bodies.end()) {
            if (e.entity->has<Box2DHitbox>()) {
                removeHitboxFromBodyOf(*entity, *e.property);
            } else {
                despawnInBox2D(*entity);
            }
        } else {
            // Illegal state
            // If there exists an entity from which we remove a hitbox, we should have none before that it had a hitbox.
            PAX_THROW_RUNTIME_ERROR("Illegal state");
        }
    }

    void Box2DWorld::onRigidBodySpawned(PropertyAttachedEvent<GameEntity, Box2DRigidBody> &e) {
//        PAX_LOG(Log::Level::Info, "");

    }

    void Box2DWorld::onRigidBodyDespawned(PropertyDetachedEvent<GameEntity, Box2DRigidBody> &e) {
//        PAX_LOG(Log::Level::Info, "");

    }
}