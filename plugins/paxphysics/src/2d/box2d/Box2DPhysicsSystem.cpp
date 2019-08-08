//
// Created by Paul on 21.01.2018.
//

#include <paxphysics/2d/box2d/Box2DWorld.h>
#include "paxphysics/2d/box2d/Box2DPhysicsSystem.h"

namespace PAX::Physics {
    Box2DPhysicsSystem::Box2DPhysicsSystem(float pixelsPerMeter) {
        setPixelsPerMeter(pixelsPerMeter);
    }

    void Box2DPhysicsSystem::initialize(Game *game) {
        EntityPropertySystem<PAX::Physics::Box2DHitbox>::initialize(game);
    }

    void Box2DPhysicsSystem::setPixelsPerMeter(float pixelsPerMeter) {
        this->pixelsPerMeter = pixelsPerMeter;
        this->metersPerPixel = 1.f / pixelsPerMeter;
    }

    float Box2DPhysicsSystem::getMetersPerPixel() {
        return metersPerPixel;
    }

    float Box2DPhysicsSystem::getPixelsPerMeter() {
        return pixelsPerMeter;
    }

    void Box2DPhysicsSystem::update(UpdateOptions & options) {
        EntityPropertySystem<PAX::Physics::Box2DHitbox>::update(options);

        for (WorldLayer * layer : getWorldLayers()) {
            if (Box2DWorld * world = layer->get<Box2DWorld>()) {
                // synchronize engine state to Box2D
                for (Entity * entity : getEntities(layer)) {
                    entity->get<Box2DHitbox>()->synchronizeBox2D(metersPerPixel);
                }

                world->step(options);

                // synchronize state in Box2D to engine
                for (Entity * entity : getEntities(layer)) {
                    entity->get<Box2DHitbox>()->synchronizePaxEngine(pixelsPerMeter);
                }
            }
        }
    }
}