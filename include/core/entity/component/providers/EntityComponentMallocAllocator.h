//
// Created by Paul on 22.11.2017.
//

#ifndef PAXENGINE3_ENTITYCOMPONENTNEWALLOCATOR_H
#define PAXENGINE3_ENTITYCOMPONENTNEWALLOCATOR_H

#include "../../EntityComponentProvider.h"
#include <cstdlib>

namespace PAX {
    template<class EntityComponentType>
    class EntityComponentMallocAllocator : public EntityComponentProvider<EntityComponentType> {
    public:
        virtual EntityComponentType* allocate() override {
            return static_cast<EntityComponentType*>(malloc(sizeof(EntityComponentType)));
        }

        virtual void deallocate(EntityComponentType *component) override {
            component->~EntityComponentType();
            free(component);
        }
    };
}

#endif //PAXENGINE3_ENTITYCOMPONENTNEWALLOCATOR_H
