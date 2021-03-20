//
// Created by Paul Bittner on 07.02.2021.
//

#include <paxcore/system/gameentity/GameEntityPropertyPool.h>
#include <paxcore/gameentity/GameEntityProperty.h>

namespace PAX {
    bool GameEntityChunkValidator::isValid(const PoolAllocator &pool, PoolAllocator::Index i) const {
        static DefaultChunkValidator d;
        if (d.isValid(pool, i)) {
            return static_cast<GameEntityProperty *>(pool.getData(i))->getWorld();
        }
        return false;
    }

    // TODO: Maybe also cache a world pointer in the properties to speed things up a bit.
    bool GameEntityIsInWorldChunkValidator::isValid(const PoolAllocator &pool, PoolAllocator::Index i) const {
        static DefaultChunkValidator d;
        if (d.isValid(pool, i)) {
            return static_cast<GameEntityProperty *>(pool.getData(i))->getWorld() == world;
        }
        return false;
    }
}