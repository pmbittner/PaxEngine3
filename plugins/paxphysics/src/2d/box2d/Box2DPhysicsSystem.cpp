//
// Created by Paul on 21.01.2018.
//

#include <paxphysics/2d/box2d/Box2DWorld.h>
#include "paxphysics/2d/box2d/Box2DPhysicsSystem.h"

namespace PAX::Physics {
    Box2DPhysicsSystem::Box2DPhysicsSystem(float pixelsPerMeter) : hitboxes() {
        setPixelsPerMeter(pixelsPerMeter);
    }

    void Box2DPhysicsSystem::initialize(Game *game) {

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
        for (World * world : getGame()->getWorlds()) {
            if (Box2DWorld * b2world = world->get<Box2DWorld>()) {
                // synchronize engine state to Box2D
                for (const auto& hitbox : hitboxes) {
                    hitbox->synchronizeBox2D(metersPerPixel);
                }

                b2world->step(options);

                // synchronize state in Box2D to engine
                for (const auto& hitbox : hitboxes) {
                    hitbox->synchronizePaxEngine(pixelsPerMeter);
                }
            }
        }
    }

    void Box2DPhysicsSystem::toggleShowHitboxes() {
        if (showingHitboxes) {
            for (Hitbox2D * h : hitboxes) {
                h->hide();
            }
        } else {
            for (Hitbox2D * h : hitboxes) {
                h->show();
            }
        }

        showingHitboxes = !showingHitboxes;
    }
}