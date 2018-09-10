//
// Created by paul on 19.05.18.
//

#ifndef PAXENGINE3_FACTORY_H
#define PAXENGINE3_FACTORY_H

#include <memory>

namespace PAX {
    class IFactory {
    public:
        virtual ~IFactory() {}
    };

    template<typename Resource>
    class FactoryT : public IFactory {};

    template<typename Resource, typename... Params>
    class Factory : public FactoryT<Resource> {
    public:
        virtual std::shared_ptr<Resource> create(Params...) = 0;
    };
}

#endif //PAXENGINE3_FACTORY_H
