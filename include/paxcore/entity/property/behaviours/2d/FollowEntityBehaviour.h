//
// Created by Paul on 20.01.2018.
//

#ifndef PAXENGINE3_FOLLOWENTITYBEHAVIOUR_H
#define PAXENGINE3_FOLLOWENTITYBEHAVIOUR_H

#include <paxcore/entity/property/Behaviour.h>
#include <paxcore/entity/EntityIDService.h>

namespace PAX {
    class FollowEntityBehaviour : public PAX::Behaviour {
        PAX_PROPERTY(FollowEntityBehaviour, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(PAX::Behaviour)
        PAX_PROPERTY_IS_SINGLE

        EntityID targetID = 0;
        float speed = 2.5f;

        bool respectWorldSize = false;

    public:
        explicit FollowEntityBehaviour(EntityID targetID = EntityIDService::InvalidID);

        void update(UpdateOptions & options) override;

        bool respectsWorldSize();
        void shouldRespectWorldSize(bool respectWorldSize);

        void setTarget(EntityID id);
        EntityID getTarget() const;
    };
}

#endif //PAXENGINE3_FOLLOWENTITYBEHAVIOUR_H
