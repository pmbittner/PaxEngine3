//
// Created by Paul on 22.11.2017.
//

#ifndef PAXENGINE3_ENTITYCOMPONENTSERVICE_H
#define PAXENGINE3_ENTITYCOMPONENTSERVICE_H

#include <assert.h>
#include <utility>

#include <utility/TypeMap.h>
#include <core/entity/component/providers/EntityComponentMallocAllocator.h>
#include "EntityComponentProvider.h"
#include "EntityComponent.h"

namespace PAX {
    class EntityComponentService {
        TypeMap<void*> _registeredProviders;

    private:
        template<class EntityComponentType>
        EntityComponentProvider<EntityComponentType>* getProviderFor() {
            if (_registeredProviders.contains<EntityComponentType>())
                return static_cast<EntityComponentProvider<EntityComponentType>*>(_registeredProviders.get<EntityComponentType>());
            return nullptr;
        }

        /*
        EntityComponentProvider<EntityComponent>* getProviderFor(std::type_index index) {
            if (_registeredProviders.contains(index))
                return static_cast<EntityComponentProvider<EntityComponent>*>(_registeredProviders.get(index));
            return nullptr;
        }
        //*/

    public:
        template<class EntityComponentType>
        bool registerProvider(EntityComponentProvider<EntityComponentType> *provider) {
            return _registeredProviders.put<EntityComponentType>(provider);
        }

        template<class EntityComponentType>
        size_t unregisterProvider() {
            return _registeredProviders.erase<EntityComponentType>();
        }

        /**
         * This will return an instance of the given EntityComponent type.
         * If no provider for the given type is registered, a EntityComponentNewAllocator will be registered for it.
         */
        template<class EntityComponentType, typename... Args>
        EntityComponentType* create(Args... args) {
            EntityComponentProvider<EntityComponentType>* provider = getProviderFor<EntityComponentType>();

            if (!provider) {
                provider = new EntityComponentMallocAllocator<EntityComponentType>();
                registerProvider<EntityComponentType>(provider);
            }

            EntityComponentType* memory = provider->allocate();
            provider->construct(memory, std::forward<Args>(args)...);
            return memory;
        }

        template<class EntityComponentType>
        void free(EntityComponentType *component) {
            EntityComponentProvider<EntityComponentType>* provider = getProviderFor<EntityComponentType>();
            assert(provider && ("No provider is registered for the given type! The component was either created externally or the provider for its type was unregistered!"));
            provider->deallocate(component);
        }

        void free(std::type_index index, EntityComponent *component) {
            /*
            EntityComponentProvider<EntityComponent>* provider = getProviderFor(index);
            assert(provider && ("No provider is registered for the given type! The component was either created externally or the provider for its type was unregistered!"));
            provider->deallocate(component);
            //*/
        }
    };
}

#endif //PAXENGINE3_ENTITYCOMPONENTSERVICE_H
