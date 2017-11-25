//
// Created by Paul on 22.11.2017.
//

#ifndef PAXENGINE3_ENTITYCOMPONENTSERVICE_H
#define PAXENGINE3_ENTITYCOMPONENTSERVICE_H

#include <assert.h>
#include <utility>

#include <utility/TypeMap.h>
#include <core/entity/component/allocators/EntityComponentMallocAllocator.h>
#include "EntityComponentAllocator.h"
#include "EntityComponent.h"

namespace PAX {
    class EntityComponentService {
        TypeMap<void*> _allocators;

    private:
        template<class EntityComponentType>
        EntityComponentAllocator<EntityComponentType>* getAllocatorFor() {
            if (_allocators.contains<EntityComponentType>())
                return static_cast<EntityComponentAllocator<EntityComponentType>*>(_allocators.get<EntityComponentType>());
            return nullptr;
        }

        /*
        EntityComponentAllocator<EntityComponent>* getProviderFor(std::type_index index) {
            if (_allocators.contains(index))
                return static_cast<EntityComponentAllocator<EntityComponent>*>(_allocators.get(index));
            return nullptr;
        }
        //*/

    public:
        template<class EntityComponentType>
        bool registerProvider(EntityComponentAllocator<EntityComponentType> *provider) {
            return _allocators.put<EntityComponentType>(provider);
        }

        template<class EntityComponentType>
        size_t unregisterProvider() {
            return _allocators.erase<EntityComponentType>();
        }

        /**
         * This will return an instance of the given EntityComponent type.
         * If no provider for the given type is registered, a EntityComponentNewAllocator will be registered for it.
         */
        template<class EntityComponentType, typename... Args>
        EntityComponentType* create(Args... args) {
            EntityComponentAllocator<EntityComponentType>* allocator = getAllocatorFor<EntityComponentType>();

            if (!allocator) {
                allocator = new EntityComponentMallocAllocator<EntityComponentType>();
                registerProvider<EntityComponentType>(allocator);
            }

            EntityComponentType* memory = allocator->allocate();
            allocator->construct(memory, std::forward<Args>(args)...);
            return memory;
        }

        template<class EntityComponentType>
        void free(EntityComponentType *component) {
            EntityComponentAllocator<EntityComponentType>* provider = getAllocatorFor<EntityComponentType>();
            assert(provider && ("No provider is registered for the given type! The component was either created externally or the provider for its type was unregistered!"));
            provider->destruct(component);
            provider->deallocate(component);
        }

        /*
    void free(std::type_index index, EntityComponent *component) {
        EntityComponentAllocator<EntityComponent>* provider = getProviderFor(index);
        assert(provider && ("No provider is registered for the given type! The component was either created externally or the provider for its type was unregistered!"));
        provider->deallocate(component);
        }
        //*/
    };
}

#endif //PAXENGINE3_ENTITYCOMPONENTSERVICE_H
