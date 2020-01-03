//
// Created by Paul on 20.01.2018.
//

#ifndef PAXENGINE3_FOLLOWENTITYBEHAVIOUR_H
#define PAXENGINE3_FOLLOWENTITYBEHAVIOUR_H

#include <paxcore/entity/property/Behaviour.h>
#include <paxcore/entity/GameEntityIDService.h>

namespace PAX {
    class FollowGameEntityBehaviour : public PAX::Behaviour {
        PAX_PROPERTY(FollowGameEntityBehaviour, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(PAX::Behaviour)
        PAX_PROPERTY_IS_SINGLE

        GameEntityID targetID = 0;
        float speed = 2.5f;

        bool respectWorldSize = false;

    public:
        explicit FollowGameEntityBehaviour(GameEntityID targetID = GameEntityIDService::InvalidID);

        void update(UpdateOptions & options) override;

        bool respectsWorldSize();
        void shouldRespectWorldSize(bool respectWorldSize);

        void setTarget(GameEntityID id);
        GameEntityID getTarget() const;
    };
}

#endif //PAXENGINE3_FOLLOWENTITYBEHAVIOUR_H
