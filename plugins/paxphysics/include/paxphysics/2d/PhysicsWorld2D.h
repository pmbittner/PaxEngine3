//
// Created by Paul on 28.07.2019.
//

#ifndef PAXENGINE3_PHYSICSWORLD2D_H
#define PAXENGINE3_PHYSICSWORLD2D_H

#include <paxcore/world/WorldProperty.h>

namespace PAX::Physics {
    class PhysicsWorld2D : public WorldProperty {
        PAX_PROPERTY(PAX::Physics::PhysicsWorld2D, PAX_PROPERTY_IS_ABSTRACT)
        PAX_PROPERTY_DERIVES(WorldProperty)
        PAX_PROPERTY_IS_SINGLE
        
        glm::vec2 gravity;
    
    public:
        explicit PhysicsWorld2D(const glm::vec2 & gravity);
        
        virtual void setGravity(const glm::vec2 & gravity);
        const glm::vec2 & getGravity();
    };
}

#endif //PAXENGINE3_PHYSICSWORLD2D_H
