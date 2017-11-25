//
// Created by Paul on 11.05.2017.
//

#ifndef PAXENGINE3_ENTITYCOMPONENTPROVIDER_H
#define PAXENGINE3_ENTITYCOMPONENTPROVIDER_H

namespace PAX {
    template<class EntityComponentType>
    class EntityComponentAllocator {
    public:
        template<typename... Args>
        EntityComponentType* construct(EntityComponentType* component, Args... args) {
            return new (component) EntityComponentType(std::forward<Args>(args)...);
        }

        void destruct(EntityComponentType* component) {
            component->~EntityComponentType();
        }

        virtual EntityComponentType* allocate() = 0;
        virtual void deallocate(EntityComponentType *component) = 0;
    };
}

#endif //PAXENGINE3_ENTITYCOMPONENTPROVIDER_H
