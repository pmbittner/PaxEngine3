//
// Created by paul on 07.01.19.
//

#ifndef PAXENGINE3_GENERICFACTORYSERVICE_H
#define PAXENGINE3_GENERICFACTORYSERVICE_H

#include <vector>
#include <polypropylene/reflection/TypeMap.h>
#include "GenericFactory.h"

namespace PAX {
    class GenericFactoryService {
        TypeMap<std::vector<IGenericFactory*>> _factories;

        template<typename Resource, typename... Params>
        GenericFactory<Resource, Params...>* getFactory() {
            std::vector<IGenericFactory *> &possibleFactories = _factories[paxtypeof(Resource)];
            for (IGenericFactory *possibleFactory : possibleFactories) {
                GenericFactory<Resource, Params...> *factory = dynamic_cast<GenericFactory<Resource, Params...> *>(possibleFactory);
                if (factory)
                    return factory;
            }

            return nullptr;
        }

    public:
        template<typename Resource>
        void registerFactory(GenericFactoryT<Resource>* loader) {
            _factories[paxtypeof(Resource)].push_back(loader);
        }

        /**
         * Creates the resource of the given Type with the given parameters. This will only succeed if a
         * Factory is registered for this type, that can create the given signature. The caller will get ownership
         * of the returned object in form of a shared pointer.
         */
        template<typename Resource, typename... Params>
        std::shared_ptr<Resource> create(Params... p) {
            GenericFactory<Resource, Params...> *factory = getFactory<Resource, Params...>();
            if (factory)
                return factory->create(std::forward<Params>(p)...);
            return nullptr;
        }
    };
}

#endif //PAXENGINE3_GENERICFACTORYSERVICE_H
