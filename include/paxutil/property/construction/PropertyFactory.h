//
// Created by paul on 06.01.19.
//

#ifndef PAXENGINE3_PROPERTYFACTORY_H
#define PAXENGINE3_PROPERTYFACTORY_H

#include <string>
#include <unordered_map>
#include <paxutil/reflection/TypeRegister.h>

namespace PAX {
    template<typename C>
    class Property;

    class ContentProvider {
    public:
        template<typename T>
        T provide() {
            return T();
        }
    };

    // This is just for testing
    template<>
    std::string ContentProvider::provide();
    template<>
    int ContentProvider::provide();

    template<class C>
    class PropertyFactory {
    public:
        virtual Property<C> * create(ContentProvider & contentProvider) = 0;
    };

    template<class C>
    class PropertyFactoryRegister {
    public:
        static PropertyFactory<C> * getFactoryFor(const std::string & name) {
            const auto & map = getMap();
            const auto & it = map.find(name);

            if (it != map.end())
                return it->second;

            return nullptr;
        }

    protected:
        using MapType = std::unordered_map<std::string, PropertyFactory<C>*>;

        // Use this method to save the map to avoid the Static Initialization Order Fiasko.
        static MapType & getMap() noexcept {
            static MapType map;
            return map;
        }

        static void registerFactory(const std::string & name, PropertyFactory<C>* constructor) noexcept {
            getMap()[name] = constructor;
        }
    };

    template<typename PropertyType, typename C>
    class PropertyRegister : private PropertyFactoryRegister<C>, public PropertyFactory<C> {
    public:
        explicit PropertyRegister(const std::string & name) noexcept : PropertyFactory<C>() {
            PropertyFactoryRegister<C>::registerFactory(name, this);
        }

        Property<C> * create(ContentProvider & contentProvider) override {
            return PropertyType::constructFromProvider(contentProvider);
        }
    };
}

#endif //PAXENGINE3_PROPERTYFACTORY_H
