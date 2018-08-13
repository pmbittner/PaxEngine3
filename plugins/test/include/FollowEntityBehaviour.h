//
// Created by Paul on 20.01.2018.
//

#ifndef PAXENGINE3_FOLLOWENTITYBEHAVIOUR_TEST_PLUGIN_H
#define PAXENGINE3_FOLLOWENTITYBEHAVIOUR_TEST_PLUGIN_H

#include <core/entity/component/Behaviour.h>

namespace PaxTestPlugin {
    class FollowEntityBehaviour : public PAX::Behaviour {
        PAX_ENTITYCOMPONENT_BODY(PAX::Behaviour, false)

        PAX::Entity *target = nullptr;
        float speed = 0.09f;

        int lolIEditSthaasasdasdasdasdg;
        int jamasdasdasadsasdasdadsan;
    public:
        FollowEntityBehaviour(PAX::Entity *target) : target(target) {}

        virtual void update() override {
            if (target) {
                PAX::Transform &me = getOwner()->getTransform();
                PAX::Transform &he = target->getTransform();
                me.position2D() = me.position2D() + (he.position2D() - me.position2D()) * speed;
            }
        }
    };
}

#endif //PAXENGINE3_FOLLOWENTITYBEHAVIOUR_TEST_PLUGIN_H
