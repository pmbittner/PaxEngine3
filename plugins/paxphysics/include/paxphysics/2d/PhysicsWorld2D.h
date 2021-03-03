//
// Created by Paul on 28.07.2019.
//

#ifndef PAXENGINE3_PHYSICSWORLD2D_H
#define PAXENGINE3_PHYSICSWORLD2D_H

#include <paxcore/world/WorldProperty.h>
#include "event/Collision.h"

namespace PAX::Physics {
    class PhysicsWorld2D : public WorldProperty {
        PAX_PROPERTY(PAX::Physics::PhysicsWorld2D, PAX_PROPERTY_IS_ABSTRACT)
        PAX_PROPERTY_DERIVES(WorldProperty)
        PAX_PROPERTY_IS_SINGLE

        std::vector<Collision> activeCollisions;
        glm::vec2 gravity;

        static void TriggerHitBeginEvents(Hitbox2D * me, Hitbox2D * other, const Collision & c);
        static void TriggerHitEndEvents(Hitbox2D * me, Hitbox2D * other, const Collision & c);

    protected:
        void onHitBegin(const Collision & c);
        void onHitEnd(const Collision & c);

    public:
        explicit PhysicsWorld2D(const glm::vec2 & gravity);

        PAX_NODISCARD ClassMetadata getMetadata() override;
        
        virtual void setGravity(const glm::vec2 & gravity);
        const glm::vec2 & getGravity();
        PAX_NODISCARD const std::vector<Collision> & getCurrentCollisions() const;
    };
}

#endif //PAXENGINE3_PHYSICSWORLD2D_H
