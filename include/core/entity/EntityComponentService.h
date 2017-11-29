//
// Created by Paul on 22.11.2017.
//

#ifndef PAXENGINE3_ENTITYCOMPONENTSERVICE_H
#define PAXENGINE3_ENTITYCOMPONENTSERVICE_H

#include <assert.h>
#include <utility>
#include <unordered_set>

#include <utility/TypeMap.h>
#include <core/entity/component/allocators/EntityComponentMallocAllocator.h>

#include "EntityComponentAllocator.h"
#include "EntityComponent.h"

namespace PAX {
    class EntityComponentService {
        TypeMap<UntypedEntityComponentAllocator*> _allocators;
        std::unordered_set<EntityComponent*> _allocatedComponents;

        template<class EntityComponentType>
        EntityComponentAllocator<EntityComponentType>* getAllocatorFor() {
            if (_allocators.contains<EntityComponentType>())
                return static_cast<EntityComponentAllocator<EntityComponentType> *>(_allocators.get<EntityComponentType>());
            return nullptr;
        }

        UntypedEntityComponentAllocator* getAllocatorFor(std::type_index index) {
            if (_allocators.contains(index))
                return _allocators.get(index);
            return nullptr;
        }

    public:
        EntityComponentService() {
        }

        template<class EntityComponentType>
        bool registerAllocator(EntityComponentAllocator<EntityComponentType> *provider) {
            return _allocators.put<EntityComponentType>(provider);
        }

        template<class EntityComponentType>
        size_t unregisterAllocator() {
            return _allocators.erase<EntityComponentType>();
        }

        /**
         * This will return an instance of the given EntityComponent type.
         * If no provider for the given type is registered, a EntityComponentMallocAllocator will be registered for it.
         */
        template<class EntityComponentType, typename... Args>
        EntityComponentType* create(Args... args) {
            EntityComponentAllocator<EntityComponentType>* allocator = getAllocatorFor<EntityComponentType>();

            if (!allocator) {
                allocator = new EntityComponentMallocAllocator<EntityComponentType>();
                registerAllocator<EntityComponentType>(allocator);
            }

            EntityComponentType* memory = allocator->allocate();
            allocator->construct(memory, std::forward<Args>(args)...);
            _allocatedComponents.insert(memory);

            return memory;
        }

        template<class EntityComponentType>
        void free(EntityComponentType *component) {
            if (_allocatedComponents.count(component) > 0) {
                EntityComponentAllocator<EntityComponentType>* allocator = getAllocatorFor<EntityComponentType>();
                assert(allocator && ("No provider is registered for the given type! The component was either created externally or the provider for its type was unregistered!"));

                allocator->destruct(component);
                allocator->deallocate(component);
                _allocatedComponents.erase(component);
            }
        }

        void free(std::type_index index, EntityComponent *component) {
            if (_allocatedComponents.count(component) > 0) {
                UntypedEntityComponentAllocator* allocator = getAllocatorFor(index);
                assert(allocator && ("No provider is registered for the given type! The component was either created externally or the provider for its type was unregistered!"));

                allocator->untypedDestructAndDeallocate(component);
                _allocatedComponents.erase(component);
            }
        }
    };
}

#endif //PAXENGINE3_ENTITYCOMPONENTSERVICE_H
