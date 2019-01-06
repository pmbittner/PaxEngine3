//
// Created by Paul on 20.01.2018.
//

#ifndef PAXENGINE3_FOLLOWENTITYBEHAVIOUR_H
#define PAXENGINE3_FOLLOWENTITYBEHAVIOUR_H

#include <paxcore/entity/component/Behaviour.h>

namespace PAX {
    class FollowEntityBehaviour : public PAX::Behaviour {
        PAX_PROPERTY(FollowEntityBehaviour)
        PAX_PROPERTY_DERIVES(PAX::Behaviour)
        PAX_PROPERTY_IS_SINGLE

        Entity *target = nullptr;
        float speed = 2.5f;

    public:
        explicit FollowEntityBehaviour(Entity *target) : target(target) {}

        void update() override;
    };
}

#endif //PAXENGINE3_FOLLOWENTITYBEHAVIOUR_H
