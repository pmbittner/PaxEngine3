//
// Created by paul on 07.01.19.
//

#ifndef PAXENGINE3_GENERICFACTORY_H
#define PAXENGINE3_GENERICFACTORY_H

#include <memory>

namespace PAX {
    class IGenericFactory {
    public:
        virtual ~IGenericFactory() {}
    };

    template<typename Resource>
    class GenericFactoryT : public IGenericFactory {};

    template<typename Resource, typename... Params>
    class GenericFactory : public GenericFactoryT<Resource> {
    public:
        virtual std::shared_ptr<Resource> create(Params...) = 0;
    };
}

#endif //PAXENGINE3_GENERICFACTORY_H
