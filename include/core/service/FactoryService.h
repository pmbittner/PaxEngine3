//
// Created by paul on 19.05.18.
//

#ifndef PAXENGINE3_FACTORYSERVICE_H
#define PAXENGINE3_FACTORYSERVICE_H

#include <vector>
#include <easylogging++.h>

#include "Factory.h"

#include <utility/datastructures/TypeMap.h>
#include <utility/Signature.h>
#include <utility/reflection/TemplateTypeToString.h>

namespace PAX {
    class FactoryService {
        TypeMap<std::vector<IFactory*>> _factories;

        template<typename Resource, typename... Params>
        Factory<Resource, Params...>* getFactory() {
            //LOG(INFO) << "[FactoryService] getFactory for " << Reflection::GetTypeName<Resource>() << std::endl;
            std::vector<IFactory *> &possibleFactories = _factories.get<Resource>();
            for (IFactory *possibleFactory : possibleFactories) {
                Factory<Resource, Params...> *factory = dynamic_cast<Factory<Resource, Params...> *>(possibleFactory);
                //LOG(INFO) << "[FactoryService]     check Loader " << possibleFactory << " == " << factory << std::endl;
                if (factory)
                    return factory;
            }

            return nullptr;
        }

    public:
        template<typename Resource>
        void registerFactory(FactoryT<Resource>* loader) {
            _factories.get<Resource>().push_back(loader);
        }

        /**
         * Creates the resource of the given Type with the given parameters. This will only succeed if a
         * Factory is registered for this type, that can create the given signature. The caller will get ownership
         * of the returned object in form of a shared pointer.
         */
        template<typename Resource, typename... Params>
        std::shared_ptr<Resource> create(Params... p) {
            Factory<Resource, Params...> *loader = getFactory<Resource, Params...>();
            if (loader)
                return loader->create(std::forward<Params>(p)...);
            return nullptr;
        }
    };
}

#endif //PAXENGINE3_FACTORYSERVICE_H
