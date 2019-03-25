//
// Created by Paul on 21.01.2018.
//

#ifndef PAXENGINE3_BOX2DPHYSICSSYSTEM_H
#define PAXENGINE3_BOX2DPHYSICSSYSTEM_H

#include <paxcore/system/entity/EntityPropertySystem.h>
#include <Box2D/Box2D.h>

#include "Box2DRigidBody.h"

namespace PAX {
    namespace Physics {
        namespace Box2D {
            class PhysicsSystem : public EntityPropertySystem<PAX::Physics::Box2D::RigidBody> {
                b2World world;

            public:
                explicit PhysicsSystem(const glm::vec2 &gravity);

                void initialize(Game *game) override;
                void update() override;
            };
        }
    }
}

#endif //PAXENGINE3_BOX2DPHYSICSSYSTEM_H
