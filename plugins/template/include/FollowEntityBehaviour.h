//
// Created by Paul on 20.01.2018.
//

#ifndef PAXENGINE3_PAXTEMPLATEPLUGIN_FOLLOWENTITYBEHAVIOUR_H
#define PAXENGINE3_PAXTEMPLATEPLUGIN_FOLLOWENTITYBEHAVIOUR_H

#include <paxcore/entity/component/Behaviour.h>

namespace PaxTemplatePlugin {
    class FollowGameEntityBehaviour : public PAX::Behaviour {
        PAX_ENTITYCOMPONENT_BODY(PAX::Behaviour, false)

        PAX::GameEntity *target = nullptr;
        float speed = 0.09f;

    public:
        FollowGameEntityBehaviour(PAX::GameEntity *target) : target(target) {}

        virtual void update() override {
            if (target) {
                PAX::Transform &me = getOwner()->getTransform();
                PAX::Transform &he = target->getTransform();
                me.position2D() = me.position2D() + (he.position2D() - me.position2D()) * speed;
            }
        }
    };
}

#endif //PAXENGINE3_PAXTEMPLATEPLUGIN_FOLLOWENTITYBEHAVIOUR_H
