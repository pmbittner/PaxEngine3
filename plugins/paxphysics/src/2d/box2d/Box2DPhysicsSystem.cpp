//
// Created by Paul on 21.01.2018.
//

#include <paxphysics/2d/box2d/Box2DWorld.h>
#include "paxphysics/2d/box2d/Box2DPhysicsSystem.h"

namespace PAX::Physics {
    Box2DPhysicsSystem::Box2DPhysicsSystem() = default;

    void Box2DPhysicsSystem::initialize(Game *game) {
        EntityPropertySystem<PAX::Physics::Box2DHitbox>::initialize(game);
    }

    void Box2DPhysicsSystem::update(UpdateOptions & options) {
        EntityPropertySystem<PAX::Physics::Box2DHitbox>::update(options);

        for (WorldLayer * layer : getWorldLayers()) {
            if (Box2DWorld * world = layer->get<Box2DWorld>()) {
                // synchronize engine state to Box2D
                for (Entity * entity : getEntities(layer)) {
                    entity->get<Box2DHitbox>()->synchronizeBox2D();
                }

                world->step(options);

                // synchronize state in Box2D to engine
                for (Entity * entity : getEntities(layer)) {
                    entity->get<Box2DHitbox>()->synchronizePaxEngine();
                }
            }
        }
    }
}