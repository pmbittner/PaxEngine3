//
// Created by Paul on 28.09.2018.
//

#ifndef PAXENGINE3_BOX2DWORLD_H
#define PAXENGINE3_BOX2DWORLD_H

#include <Box2D/Dynamics/b2World.h>
#include <paxphysics/2d/PhysicsWorld2D.h>

namespace PAX::Physics {
    class Box2DWorld : public PhysicsWorld2D {
        PAX_PROPERTY(::PAX::Physics::Box2DWorld, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(::PAX::Physics::PhysicsWorld2D)
        PAX_PROPERTY_IS_SINGLE

        b2World box2dWorld;
        int32 velocityIterations = 8; // This value is recommended by Box2D.
        int32 positionIterations = 3; // This value is recommended by Box2D.

    public:
        explicit Box2DWorld(const glm::vec2 & gravity);

        void setGravity(const glm::vec2 & gravity) override;
        void step(UpdateOptions & options);

        b2World & getb2World();
    };
}

#endif //PAXENGINE3_BOX2DWORLD_H
