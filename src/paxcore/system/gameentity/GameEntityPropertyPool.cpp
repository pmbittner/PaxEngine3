//
// Created by Paul Bittner on 07.02.2021.
//

#include <paxcore/system/gameentity/GameEntityPropertyPool.h>
#include <paxcore/gameentity/GameEntityProperty.h>

namespace PAX {
    bool GameEntityChunkValidator::isValid(const PoolAllocator &pool, PoolAllocator::Index i) {
        if (DefaultChunkValidator::isValid(pool, i)) {
            auto * prop = static_cast<GameEntityProperty *>(pool.getData(i));
            GameEntity * owner = prop->getOwner();
            return owner && owner->getWorld();
        }
        return false;
    }
}