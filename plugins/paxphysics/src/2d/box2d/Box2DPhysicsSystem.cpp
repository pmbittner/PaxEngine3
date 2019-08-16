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
        Super::initialize(game);
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
        Super::update(options);

        // synchronize engine state to Box2D
        for (Box2DHitbox * hitbox : *this) {
            hitbox->synchronizeBox2D(metersPerPixel);
        }

        for (WorldLayer * layer : getManager()->getActiveWorld()->getLayers()) {
            if (Box2DWorld *world = layer->get<Box2DWorld>()) {
                world->step(options);
            }
        }

        // synchronize state in Box2D to engine
        for (Box2DHitbox * hitbox : *this) {
            hitbox->synchronizePaxEngine(pixelsPerMeter);
        }
    }
}