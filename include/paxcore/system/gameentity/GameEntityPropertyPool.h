//
// Created by Paul Bittner on 07.02.2021.
//

#ifndef MESHFOLD_GAMEENTITYPROPERTYPOOL_H
#define MESHFOLD_GAMEENTITYPROPERTYPOOL_H

#include "polypropylene/memory/PropertyPool.h"

namespace PAX {
    class World;

    struct PAX_MAYBEUNUSED GameEntityChunkValidator {
        PAX_NODISCARD bool isValid(const PoolAllocator & pool, PoolAllocator::Index i) const;
    };

    struct PAX_MAYBEUNUSED GameEntityIsInWorldChunkValidator {
        const World * world = nullptr;
        PAX_NODISCARD bool isValid(const PoolAllocator & pool, PoolAllocator::Index i) const;
    };

    template<class PropertyType>
    using AllGameEntityPropertiesPool = PropertyPool<PropertyType, PropertyPoolIterator<PropertyType, GameEntityChunkValidator>>;

    template<class PropertyType>
    class WorldsGameEntityPropertiesPool : public
            PropertyPool<PropertyType, PropertyPoolIterator<PropertyType, GameEntityIsInWorldChunkValidator>>
    {
        GameEntityIsInWorldChunkValidator validator;

    public:
        explicit WorldsGameEntityPropertiesPool(const World & world)
        : PropertyPool<PropertyType, PropertyPoolIterator<PropertyType, GameEntityIsInWorldChunkValidator>>()
        {
            validator.world = &world;
        }

        PAX_NODISCARD const GameEntityIsInWorldChunkValidator & getValidator() const override {
            return validator;
        }
    };
}

#endif //MESHFOLD_GAMEENTITYPROPERTYPOOL_H
