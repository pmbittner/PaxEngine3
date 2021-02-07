//
// Created by Paul Bittner on 07.02.2021.
//

#ifndef MESHFOLD_GAMEENTITYPROPERTYPOOL_H
#define MESHFOLD_GAMEENTITYPROPERTYPOOL_H

#include "polypropylene/memory/PropertyPool.h"

namespace PAX {
    struct PAX_MAYBEUNUSED GameEntityChunkValidator {
        static bool isValid(const PoolAllocator & pool, PoolAllocator::Index i);
    };

    template<class PropertyType>
    using GameEntityPropertyPool =
            PropertyPool<PropertyType, PropertyPoolIterator<PropertyType, GameEntityChunkValidator>>;
}

#endif //MESHFOLD_GAMEENTITYPROPERTYPOOL_H
