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

    Box2DWorld::Box2DWorld(const glm::vec2 & gravity) : PhysicsWorld2D(gravity), box2dWorld(ToBox2D(gravity)) {
        box2dWorld.SetAllowSleeping(false);
    }

    ClassMetadata Box2DWorld::getMetadata() {
        ClassMetadata m = Super::getMetadata();
        m.add(paxfieldof(pixelsPerMeter)).addFlag(Field::IsMandatory);
        return m;
    }

    void Box2DWorld::setGravity(const glm::vec2 &gravity) {
        Super::setGravity(gravity);
        box2dWorld.SetGravity(ToBox2D(gravity));
    }

    const b2World & Box2DWorld::getb2World() const {
        return box2dWorld;
    }

    void Box2DWorld::step(PAX::UpdateOptions &options) {
        synchronizeBox2D();
        box2dWorld.Step(options.dt, velocityIterations, positionIterations);
        synchronizePaxEngine();
    }

    void Box2DWorld::created() {
        // update Box2D
        Super::created();
        setGravity(getGravity());
        setPixelsPerMeter(pixelsPerMeter); // update inverse
    }

    void Box2DWorld::setPixelsPerMeter(float pixelsPerMeter) {
        this->pixelsPerMeter = pixelsPerMeter;
        this->metersPerPixel = 1.f / pixelsPerMeter;
    }

    float Box2DWorld::getMetersPerPixel() const {
        return metersPerPixel;
    }

    float Box2DWorld::getPixelsPerMeter() const {
        return pixelsPerMeter;
    }

    // TODO: Consider scale of engine to box2d

    void Box2DWorld::synchronizeBox2D() {
        GameEntity * entity = nullptr;
        b2Body * body = nullptr;
        for (auto & entry : bodies) {
            entity = entry.first;
            body = entry.second;
            Transformation &t = entity->getTransformation();
            body->SetTransform(ToBox2D(metersPerPixel * t.position2D()), t.getRotation2DInRadians());

            if (Movement2D * v = entity->get<Movement2D>()) {
                body->SetAngularVelocity(Math::toRadians(v->angularVelocityInDegrees));
                body->SetLinearVelocity(ToBox2D(metersPerPixel * v->velocity));
            }
        }
    }

    void Box2DWorld::synchronizePaxEngine() {
        GameEntity * entity = nullptr;
        b2Body * body = nullptr;
        for (auto & entry : bodies) {
            entity = entry.first;
            body = entry.second;
            Transformation & paxTransform = entity->getTransformation();
            const b2Transform & box2DTransform = body->GetTransform();
            paxTransform.position2D() = pixelsPerMeter * ToGLM(box2DTransform.p);
            paxTransform.setRotation2DInRadians(box2DTransform.q.GetAngle());

            if (Movement2D * v = entity->get<Movement2D>()) {
                v->velocity = pixelsPerMeter * ToGLM(body->GetLinearVelocity());
                v->angularVelocityInDegrees = Math::toDegrees(body->GetAngularVelocity());
            }
        }
    }

    void Box2DWorld::spawnInBox2D(GameEntity &entity) {
        Box2DRigidBody * rigidBody = entity.get<Box2DRigidBody>();
        const std::vector<Box2DHitbox*> & hitboxes = entity.get<Box2DHitbox>();
        const bool isRigidBody = rigidBody != nullptr;
        b2Body * body = bodies[&entity];
        if (body) {
            // This should never happen.
            box2dWorld.DestroyBody(body);
        }

        b2BodyDef bodyDef;
        bodyDef.type = ToBox2D(entity.getMotionType());
        if (isRigidBody) {
            bodyDef.fixedRotation = rigidBody->hasFixedRotation();
        }
        body = box2dWorld.CreateBody(&bodyDef);
        body->SetUserData(&entity);
        bodies[&entity] = body;

        if (isRigidBody) {
            rigidBody->body = body;
        }

        for (Box2DHitbox * hitbox : hitboxes) {
            addHitboxToBodyOf(entity, *hitbox);
        }

        body->ResetMassData();
    }

    void Box2DWorld::despawnInBox2D(GameEntity &entity) {
        if (b2Body * body = bodies[&entity]) {
            box2dWorld.DestroyBody(body);
            bodies.erase(&entity);
            if (Box2DRigidBody * rigidBody = entity.get<Box2DRigidBody>()) {
                rigidBody->body = nullptr;
            }
        }
    }

    void Box2DWorld::addHitboxToBodyOf(GameEntity &entity, Box2DHitbox &hitbox) {
        b2Body * body = bodies[&entity];
        if (!body) {
            spawnInBox2D(entity);
            return;
        }

        const bool isRigidBody = entity.has<Box2DRigidBody>();
        const std::shared_ptr<Shape2D> & shape = hitbox.getShape();
        const std::shared_ptr<PhysicsMaterial> & material = hitbox.getMaterial();
        b2Shape *bshape = ToBox2D(*shape, metersPerPixel);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = bshape;
        fixtureDef.density = material->density;
        fixtureDef.friction = material->friction;
        fixtureDef.restitution = material->elasticity;
        fixtureDef.userData = &hitbox;
        fixtureDef.isSensor = !isRigidBody || hitbox.isTriggerArea();
        hitbox.fixture = body->CreateFixture(&fixtureDef);

        /// "Box2D does not keep a reference to the shape. It clones the data into a new b2Shape object."
        delete bshape;
    }

    void Box2DWorld::removeHitboxFromBodyOf(GameEntity &entity, Box2DHitbox &hitbox) {
        b2Body * body = bodies[&entity];
        if (!body) {
            return;
        }
        body->DestroyFixture(hitbox.fixture);
        hitbox.fixture = nullptr;
    }

    void Box2DWorld::turnIntoRigidBody(GameEntity &entity, Box2DRigidBody &rigidBody) {
        b2Body * body = bodies[&entity];
        if (!body) {
            spawnInBox2D(entity);
            return;
        }

        for (
                b2Fixture * fixture = body->GetFixtureList();
                fixture != nullptr;
                fixture = fixture->GetNext())
        {
            Box2DHitbox * hitbox = static_cast<Box2DHitbox *>(fixture->GetUserData());
            fixture->SetSensor(hitbox->isTriggerArea());
        }
    }

    void Box2DWorld::removeRigidBody(GameEntity &entity, Box2DRigidBody &rigidBody) {
        b2Body * body = bodies[&entity];
        if (!body) {
            return;
        }

        for (
                b2Fixture * fixture = body->GetFixtureList();
                fixture != nullptr;
                fixture = fixture->GetNext())
        {
            fixture->SetSensor(true);
        }
    }

    void Box2DWorld::attached(World &world) {
        Super::attached(world);
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
        Super::detached(world);
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
        if (e.entity->has<Box2DHitbox>()) {
            spawnInBox2D(*e.entity);
        }
    }

    void Box2DWorld::onGameEntityDespawned(GameEntityDespawnedEvent &e) {
        if (e.entity->has<Box2DHitbox>()) {
            despawnInBox2D(*e.entity);
        }
    }

    void Box2DWorld::onHitboxSpawned(PropertyAttachedEvent<GameEntity, Box2DHitbox> &e) {
        GameEntity * entity = e.entity;
        auto it = bodies.find(entity);
        if (it == bodies.end()) {
            spawnInBox2D(*entity);
        } else {
            addHitboxToBodyOf(*entity, *e.property);
        }
    }

    void Box2DWorld::onHitboxDespawned(PropertyDetachedEvent<GameEntity, Box2DHitbox> &e) {
        GameEntity * entity = e.entity;
        // If the entity still has other hitboxes
        if (e.entity->has<Box2DHitbox>()) {
            removeHitboxFromBodyOf(*entity, *e.property);
        } else {
            // The entity does not have any hitboxes anymore.
            despawnInBox2D(*entity);
        }
    }

    void Box2DWorld::onRigidBodySpawned(PropertyAttachedEvent<GameEntity, Box2DRigidBody> &e) {
        GameEntity * entity = e.entity;
        auto it = bodies.find(entity);
        if (it == bodies.end()) {
            spawnInBox2D(*entity);
        } else {
            turnIntoRigidBody(*entity, *e.property);
        }
    }

    void Box2DWorld::onRigidBodyDespawned(PropertyDetachedEvent<GameEntity, Box2DRigidBody> &e) {
        GameEntity * entity = e.entity;
        if (entity->has<Hitbox2D>()) {
            removeRigidBody(*entity, *e.property);
        } else {
            // There are neither a rigidbody nor hitboxes attached to this entity anymore.
            despawnInBox2D(*entity);
        }
    }
}