//
// Created by Paul on 20.01.2018.
//

#ifndef PAXENGINE3_FOLLOWENTITYBEHAVIOUR_H
#define PAXENGINE3_FOLLOWENTITYBEHAVIOUR_H

#include <paxcore/gameentity/property/Behaviour.h>
#include <paxcore/gameentity/GameEntityIDService.h>

namespace PAX {
    class FollowGameEntityBehaviour : public PAX::Behaviour {
        PAX_PROPERTY(FollowGameEntityBehaviour, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(PAX::Behaviour)
        PAX_PROPERTY_IS_SINGLE

        GameEntityID targetID = GameEntityIDService::InvalidID;
        float speed = 2.5f;

        bool respectWorldSize = false;

    public:
        explicit FollowGameEntityBehaviour(GameEntityID targetID = GameEntityIDService::InvalidID);

        void update(UpdateOptions & options) override;

        PAX_NODISCARD bool respectsWorldSize() const;
        void shouldRespectWorldSize(bool respectWorldSize);

        void setTarget(GameEntityID id);
        PAX_NODISCARD GameEntityID getTarget() const;

        PAX_NODISCARD ClassMetadata getMetadata() override;
    };
}

#endif //PAXENGINE3_FOLLOWENTITYBEHAVIOUR_H
