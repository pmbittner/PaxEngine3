//
// Created by Paul on 08.05.2017.
//

#ifndef PAXENGINE3_GAMEENTITYSPAWNEDEVENT_H
#define PAXENGINE3_GAMEENTITYSPAWNEDEVENT_H

#include "../../gameentity/GameEntity.h"
#include "../../gameentity/event/GameEntityEvent.h"

namespace PAX {
    struct GameEntitySpawnedEvent : public GameEntityEvent {
        GameEntitySpawnedEvent(GameEntity *entity) : GameEntityEvent(entity) {}
    };
}

#endif //PAXENGINE3_GAMEENTITYSPAWNEDEVENT_H
