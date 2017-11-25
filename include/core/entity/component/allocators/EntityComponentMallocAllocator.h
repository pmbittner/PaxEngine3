//
// Created by Paul on 22.11.2017.
//

#ifndef PAXENGINE3_ENTITYCOMPONENTNEWALLOCATOR_H
#define PAXENGINE3_ENTITYCOMPONENTNEWALLOCATOR_H

#include "core/entity/EntityComponentAllocator.h"
#include <cstdlib>

namespace PAX {
    template<class EntityComponentType>
    class EntityComponentMallocAllocator : public EntityComponentAllocator<EntityComponentType> {
    public:
        virtual EntityComponentType* allocate() override {
            return static_cast<EntityComponentType*>(malloc(sizeof(EntityComponentType)));
        }

        virtual void deallocate(EntityComponentType *component) override {
            free(component);
        }
    };
}

#endif //PAXENGINE3_ENTITYCOMPONENTNEWALLOCATOR_H
