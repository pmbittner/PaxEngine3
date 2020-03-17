//
// Created by Paul on 08.05.2017.
//

#ifndef PAXENGINE3_GAMEENTITYDESPAWNEDEVENT_H
#define PAXENGINE3_GAMEENTITYDESPAWNEDEVENT_H

#include "../../gameentity/GameEntity.h"
#include "../../gameentity/event/GameEntityEvent.h"

namespace PAX {
    struct GameEntityDespawnedEvent : public GameEntityEvent {
        World* oldWorld = nullptr;
        GameEntityDespawnedEvent(GameEntity *entity, World* oldWorld) : GameEntityEvent(entity), oldWorld(oldWorld) {}
    };
}

#endif //PAXENGINE3_GAMEENTITYDESPAWNEDEVENT_H
