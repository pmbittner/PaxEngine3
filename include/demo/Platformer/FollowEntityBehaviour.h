//
// Created by Paul on 20.01.2018.
//

#ifndef PAXENGINE3_FOLLOWENTITYBEHAVIOUR_H
#define PAXENGINE3_FOLLOWENTITYBEHAVIOUR_H

#include <core/entity/component/Behaviour.h>

namespace PAX {
    PAX_ENTITYCOMPONENT(FollowEntityBehaviour, Behaviour, false)
    class FollowEntityBehaviour : public Behaviour {
        PAX_ENTITYCOMPONENT_BODY

        Entity *target = nullptr;

    public:
        FollowEntityBehaviour(Entity *target) : target(target) {}

        virtual void update() override {
            if (target) {
                Transform &me = getOwner()->getTransform();
                Transform &he = target->getTransform();
                me.position2D() = he.position2D();
            }
        }
    };
}

#endif //PAXENGINE3_FOLLOWENTITYBEHAVIOUR_H
