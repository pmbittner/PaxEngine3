//
// Created by Paul on 21.01.2018.
//

#include <paxphysics/2d/box2d/Box2DWorld.h>
#include "paxphysics/2d/box2d/Box2DPhysicsSystem.h"

namespace PAX::Physics {
    Box2DPhysicsSystem::Box2DPhysicsSystem() : hitboxes() {

    }

    void Box2DPhysicsSystem::initialize(Game *game) {

    }

    void Box2DPhysicsSystem::update(UpdateOptions & options) {
        for (World * world : getGame()->getWorlds()) {
            if (Box2DWorld * b2world = world->get<Box2DWorld>()) {
                b2world->step(options);
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