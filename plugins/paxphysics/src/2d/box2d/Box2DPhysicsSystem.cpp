//
// Created by Paul on 21.01.2018.
//

#include <paxphysics/2d/box2d/Box2DWorld.h>
#include "paxphysics/2d/box2d/Box2DPhysicsSystem.h"
#include "paxutil/macros/Functional.h"

namespace PAX::Physics {
    Box2DPhysicsSystem::Box2DPhysicsSystem() : Super(), hitboxes() {

    }

    void Box2DPhysicsSystem::initialize(Game *game) {
        Super::initialize(game);
    }

    void Box2DPhysicsSystem::update(UpdateOptions & options) {
        Super::update(options);
        for (World * world : getGame()->getWorlds()) {
            if (Box2DWorld * b2world = world->get<Box2DWorld>()) {
                b2world->step(options);
            }
        }
    }

    void Box2DPhysicsSystem::toggleShowHitboxes() {
        if (showingHitboxes) {
            PAX_FORALL_ON_POINTERS(hitboxes, hide());
        } else {
            PAX_FORALL_ON_POINTERS(hitboxes, show());
        }

        showingHitboxes = !showingHitboxes;
    }
}