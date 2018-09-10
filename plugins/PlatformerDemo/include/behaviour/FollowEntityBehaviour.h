//
// Created by Paul on 20.01.2018.
//

#ifndef PAXENGINE3_FOLLOWENTITYBEHAVIOUR_H
#define PAXENGINE3_FOLLOWENTITYBEHAVIOUR_H

#include <paxcore/entity/component/Behaviour.h>

namespace PAX {
    class FollowEntityBehaviour : public PAX::Behaviour {
        PAX_ENTITYCOMPONENT_BODY(PAX::Behaviour, false)

        Entity *target = nullptr;
        float speed = 0.09f;

    public:
        FollowEntityBehaviour(Entity *target) : target(target) {}

        virtual void update() override {
            if (target) {
                Transform &me = getOwner()->getTransform();
                Transform &he = target->getTransform();
                me.position2D() = me.position2D() + (he.position2D() - me.position2D()) * speed;
            }
        }
    };
}

#endif //PAXENGINE3_FOLLOWENTITYBEHAVIOUR_H
