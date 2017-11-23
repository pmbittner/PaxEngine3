//
// Created by Paul on 22.11.2017.
//

#ifndef PAXENGINE3_ENTITYCOMPONENTNEWALLOCATOR_H
#define PAXENGINE3_ENTITYCOMPONENTNEWALLOCATOR_H

#include "../../EntityComponentProvider.h"

namespace PAX {
    template<class EntityComponentType>
    class EntityComponentNewAllocator : public EntityComponentProvider<EntityComponentType> {
    public:
        virtual EntityComponentType* create() override {
            return new EntityComponentType();
        }

        virtual void free(EntityComponentType *component) override {
            delete component;
        }
    };
}

#endif //PAXENGINE3_ENTITYCOMPONENTNEWALLOCATOR_H
