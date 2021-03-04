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
        bool insideBox2DStep = false;

        std::map<GameEntity*, b2Body*> bodies;
        std::vector<b2Body*> queuedForDeletion;

        struct FixtureMetadata {
            b2Fixture & fixture;
            Box2DHitbox * hitbox;

            explicit FixtureMetadata(b2Fixture & f);
        };

        class ContactFilterDelegate : public b2ContactFilter {
        public:
            std::vector<b2ContactFilter*> contactFilters;

            /// Return true if contact calculations should be performed between these two shapes.
            /// @warning for performance reasons this is only called when the AABBs begin to overlap.
            bool ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB) override;
        } contactFilterDelegate;

        class ContactListenersDelegate : public b2ContactListener {
        public:
            std::vector<b2ContactListener*> contactListeners;
            Box2DWorld * world;

            /// Called when two fixtures begin to touch.
            void BeginContact(b2Contact* contact) override;

            /// Called when two fixtures cease to touch.
            void EndContact(b2Contact* contact) override;

            /// This is called after a contact is updated. This allows you to inspect a
            /// contact before it goes to the solver. If you are careful, you can modify the
            /// contact manifold (e.g. disable contact).
            /// A copy of the old manifold is provided so that you can detect changes.
            /// Note: this is called only for awake bodies.
            /// Note: this is called even when the number of contact points is zero.
            /// Note: this is not called for sensors.
            /// Note: if you set the number of contact points to zero, you will not
            /// get an EndContact callback. However, you may get a BeginContact callback
            /// the next step.
            void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;

            /// This lets you inspect a contact after the solver is finished. This is useful
            /// for inspecting impulses.
            /// Note: the contact manifold does not include time of impact impulses, which can be
            /// arbitrarily large if the sub-step is small. Hence the impulse is provided explicitly
            /// in a separate data structure.
            /// Note: this is only called for contacts that are touching, solid, and awake.
            void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;
        } contactListenerDelegate;
        friend ContactListenersDelegate;

        Box2DWorld();

        void synchronizeBox2D();
        void synchronizePaxEngine();
        void cleanupDeadBodies();

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
        PAX_NODISCARD b2World & getb2World();
        PAX_NODISCARD const b2World & getb2World() const;

        void addContactFilter(b2ContactFilter & filter);
        void removeContactFilter(b2ContactFilter & filter);
        PAX_NODISCARD const std::vector<b2ContactFilter*> & getContactFilters() const;

        void addContactListener(b2ContactListener & listener);
        void removeContactListener(b2ContactListener & listener);
        PAX_NODISCARD const std::vector<b2ContactListener*> & getContactListeners() const;

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
