//
// Created by Paul on 11.05.2017.
//

#ifndef PAXENGINE3_ENTITYCOMPONENTPROVIDER_H
#define PAXENGINE3_ENTITYCOMPONENTPROVIDER_H

namespace PAX {
    class EntityComponent;
    class EntityComponentService;

    class UntypedEntityComponentAllocator {
        friend class EntityComponentService;
    protected:
        virtual void untypedDestructAndDeallocate(EntityComponent* component) = 0;
    };

    template<class EntityComponentType>
    class EntityComponentAllocator : private UntypedEntityComponentAllocator {
        friend class EntityComponentService;

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

    protected:
        virtual void untypedDestructAndDeallocate(EntityComponent* component) override final {
            EntityComponentType* componentAsMyType = dynamic_cast<EntityComponentType*>(component);
            if (componentAsMyType) {
                destruct(componentAsMyType);
                deallocate(componentAsMyType);
            }
        };
    };
}

#endif //PAXENGINE3_ENTITYCOMPONENTPROVIDER_H
