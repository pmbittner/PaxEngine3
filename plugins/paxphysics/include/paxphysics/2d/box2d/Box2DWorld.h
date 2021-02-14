//
// Created by Paul on 28.09.2018.
//

#ifndef PAXENGINE3_BOX2DWORLD_H
#define PAXENGINE3_BOX2DWORLD_H

#include <box2d/b2_world.h>
#include <paxphysics/2d/PhysicsWorld2D.h>
#include "Box2DHitbox.h"
#include "Box2DRigidBody.h"

namespace PAX::Physics {
    class Box2DWorld : public PhysicsWorld2D {
        PAX_PROPERTY(::PAX::Physics::Box2DWorld, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(::PAX::Physics::PhysicsWorld2D)
        PAX_PROPERTY_IS_SINGLE

        /// Begin Fields
        float pixelsPerMeter = 1;
        /// End Fields
        float metersPerPixel = 1; // = 1.f / pixelsPerMeter

        World * paxWorld = nullptr; // cached owner
        b2World box2dWorld;
        int32 velocityIterations = 8; // This value is recommended by Box2D.
        int32 positionIterations = 3; // This value is recommended by Box2D.

        std::map<GameEntity*, b2Body*> bodies;

        Box2DWorld();

        void synchronizeBox2D();
        void synchronizePaxEngine();

        void spawnInBox2D(GameEntity & entity);
        void despawnInBox2D(GameEntity & entity);
        void addHitboxToBodyOf(GameEntity & entity, Box2DHitbox & hitbox);
        void removeHitboxFromBodyOf(GameEntity & entity, Box2DHitbox & hitbox);
        void turnIntoRigidBody(GameEntity & entity, Box2DRigidBody & rigidBody);
        void removeRigidBody(GameEntity & entity, Box2DRigidBody & rigidBody);

    public:
        explicit Box2DWorld(const glm::vec2 & gravity);

        void setGravity(const glm::vec2 & gravity) override;
        // todo: Move meters per pixel up to PhysicsWorld2D
        void setPixelsPerMeter(float pixelsPerMeter);
        PAX_NODISCARD float getMetersPerPixel() const;
        PAX_NODISCARD float getPixelsPerMeter() const;
        PAX_NODISCARD const b2World & getb2World() const;

        void step(UpdateOptions & options);

        PAX_NODISCARD ClassMetadata getMetadata() override;
        void created() override;
        void attached(World & world) override;
        void detached(World & world) override;

        void onGameEntitySpawned(GameEntitySpawnedEvent & e);
        void onGameEntityDespawned(GameEntityDespawnedEvent & e);
        void onHitboxSpawned(PropertyAttachedEvent<GameEntity, Box2DHitbox> & e);
        void onHitboxDespawned(PropertyDetachedEvent<GameEntity, Box2DHitbox> & e);
        void onRigidBodySpawned(PropertyAttachedEvent<GameEntity, Box2DRigidBody> & e);
        void onRigidBodyDespawned(PropertyDetachedEvent<GameEntity, Box2DRigidBody> & e);
    };
}

#endif //PAXENGINE3_BOX2DWORLD_H
