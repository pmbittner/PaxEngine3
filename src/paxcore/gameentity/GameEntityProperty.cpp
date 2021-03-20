//
// Created by Bittner on 04.01.2020.
//

#include <paxcore/gameentity/GameEntityProperty.h>

namespace PAX {
    PAX_PROPERTY_IMPL(GameEntityProperty)

    void GameEntityProperty::spawned() {}
    void GameEntityProperty::despawned() {}

    World * GameEntityProperty::getWorld() const {
        GameEntity * owner = getOwner();
        if (owner) {
            return owner->getWorld();
        }
        return nullptr;
    }
}