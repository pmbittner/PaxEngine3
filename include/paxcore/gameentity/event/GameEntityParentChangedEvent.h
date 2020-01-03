//
// Created by paul on 01.06.17.
//

#ifndef PAXENGINE3_ENTITYPARENTCHANGEDEVENT_H
#define PAXENGINE3_ENTITYPARENTCHANGEDEVENT_H

#include "GameEntityEvent.h"

namespace PAX {
    struct GameEntityParentChangedEvent : public GameEntityEvent {
    public:
        GameEntity *newParent, *oldParent;
        GameEntityParentChangedEvent(GameEntity *entity, GameEntity *oldParent, GameEntity *newParent) : GameEntityEvent(entity), oldParent(oldParent), newParent(newParent) {}
    };
}

#endif //PAXENGINE3_ENTITYPARENTCHANGEDEVENT_H
