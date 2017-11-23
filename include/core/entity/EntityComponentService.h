//
// Created by Paul on 22.11.2017.
//

#ifndef PAXENGINE3_ENTITYCOMPONENTSERVICE_H
#define PAXENGINE3_ENTITYCOMPONENTSERVICE_H

#include <utility/TypeMap.h>
#include <assert.h>
#include <utility/MacroIncludes.h>
#include <core/entity/component/providers/EntityComponentNewAllocator.h>
#include "EntityComponentProvider.h"
#include "EntityComponent.h"

namespace PAX {
    class EntityComponentService {
        TypeMap<EntityComponentProvider<EntityComponent>*> _registeredProviders;

    private:
        template<class EntityComponentType>
        EntityComponentProvider<EntityComponentType>* getProviderFor() {
            if (_registeredProviders.contains<EntityComponentType>())
                return static_cast<EntityComponentProvider<EntityComponentType>*>(_registeredProviders.get<EntityComponentType>());
            return nullptr;
        }

        EntityComponentProvider<EntityComponent>* getProviderFor(std::type_index index) {
            if (_registeredProviders.contains(index))
                return _registeredProviders.get(index);
            return nullptr;
        }

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
        template<class EntityComponentType>
        EntityComponentType* create() {
            EntityComponentProvider<EntityComponentType>* provider = getProviderFor<EntityComponentType>();

            if (!provider) {
                provider = new EntityComponentNewAllocator<EntityComponentType>();
                registerProvider<EntityComponentType>(provider);
            }

            return provider->create();
        }

        template<class EntityComponentType>
        void free(EntityComponentType *component) {
            EntityComponentProvider<EntityComponentType>* provider = getProviderFor<EntityComponentType>();
            assert(provider && ("No provider is registered for the given type! The component was either created externally or the provider for its type was unregistered!"));
            provider->free(component);
        }

        void free(std::type_index index, EntityComponent *component) {
            EntityComponentProvider<EntityComponent>* provider = getProviderFor(index);
            assert(provider && ("No provider is registered for the given type! The component was either created externally or the provider for its type was unregistered!"));
            provider->free(component);
        }
    };
}

#endif //PAXENGINE3_ENTITYCOMPONENTSERVICE_H
