//
// Created by Paul on 13.08.2019.
//

#ifndef PAXENGINE3_PROPERTYOWNINGSYSTEM_H
#define PAXENGINE3_PROPERTYOWNINGSYSTEM_H

#include <paxutil/memory/allocators/PoolAllocator.h>
#include "WorldSystem.h"

namespace PAX {
    template<class P>
    class PropertyOwningSystem : public WorldSystem {
        PoolAllocator<sizeof(P)> allocator;

    public:
        PropertyOwningSystem() = default;

        void initialize(Game *game) override {
            WorldSystem::initialize(game);

            AllocationService & allocationService = P::Container::GetPropertyAllocator();
            allocationService.registerAllocator(paxtypeid(P), &allocator);
        }
    };
}

#endif //PAXENGINE3_PROPERTYOWNINGSYSTEM_H
