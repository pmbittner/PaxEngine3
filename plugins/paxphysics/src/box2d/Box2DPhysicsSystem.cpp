//
// Created by Paul on 21.01.2018.
//

#include "paxphysics/box2d/Box2DPhysicsSystem.h"

namespace PAX {
    namespace Physics {
        namespace Box2D {
            PhysicsSystem::PhysicsSystem(const glm::vec2 &gravity) : world(b2Vec2(gravity.x, gravity.y)) {

            }

            void PhysicsSystem::initialize(Game *game) {

            }

            void PhysicsSystem::update() {

            }
        }
    }
}