//
// Created by paul on 06.01.19.
//

#ifndef PAXENGINE3_PROPERTYFACTORY_H
#define PAXENGINE3_PROPERTYFACTORY_H

#include <string>
#include <unordered_map>

#include "ContentProvider.h"

namespace PAX {
    template<typename C>
    class Property;

    template<class C>
    class IPropertyFactory {
    public:
        virtual Property<C> * create(ContentProvider & contentProvider) = 0;
        IPropertyFactory() noexcept = default;
        virtual ~IPropertyFactory() {}
    };

    template<class C>
    class PropertyFactoryRegister {
        using MapType = std::unordered_map<std::string, IPropertyFactory<C>*>;

        // Use this method to save the map to avoid the Static Initialization Order Fiasko.
        static MapType & getMap() noexcept {
            static MapType map;
            return map;
        }

    protected:
        PropertyFactoryRegister() noexcept = default;

        static void registerFactory(const std::string & name, IPropertyFactory<C>* constructor) noexcept {
            getMap()[name] = constructor;
        }

    public:
        virtual ~PropertyFactoryRegister() = default;

        static IPropertyFactory<C> * getFactoryFor(const std::string & name) {
            const auto & map = getMap();
            const auto & it = map.find(name);

            if (it != map.end())
                return it->second;

            return nullptr;
        }
    };

    template<typename PropertyType, typename C>
    class PropertyFactory : private PropertyFactoryRegister<C>, public IPropertyFactory<C> {
    public:
        explicit PropertyFactory(const std::string & name) noexcept : PropertyFactoryRegister<C>(), IPropertyFactory<C>() {
            PropertyFactoryRegister<C>::registerFactory(name, this);
        }

        virtual ~PropertyFactory() {}

        Property<C> * create(ContentProvider & contentProvider) override {
            return PropertyType::createFromProvider(contentProvider);
        }
    };
}

#endif //PAXENGINE3_PROPERTYFACTORY_H
