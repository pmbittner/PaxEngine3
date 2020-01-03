//
// Created by Paul on 08.05.2017.
//

#ifndef PAXENGINE3_GAMEENTITYDESPAWNEDEVENT_H
#define PAXENGINE3_GAMEENTITYDESPAWNEDEVENT_H

#include "../../gameentity/GameEntity.h"
#include "../../gameentity/event/GameEntityEvent.h"

namespace PAX {
    struct GameEntityDespawnedEvent : public GameEntityEvent {
        WorldLayer* oldWorldLayer = nullptr;
        GameEntityDespawnedEvent(GameEntity *entity, WorldLayer* oldWorldLayer) : GameEntityEvent(entity), oldWorldLayer(oldWorldLayer) {}
    };
}

#endif //PAXENGINE3_GAMEENTITYDESPAWNEDEVENT_H
