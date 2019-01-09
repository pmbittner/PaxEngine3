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
        class Constructor {
        private:
            Property<C> * (*constructor)(ContentProvider&);
        public:
            explicit Constructor(Property<C> * (*constructor)(ContentProvider&)) noexcept : constructor(constructor) {}
            Constructor() noexcept : Constructor(nullptr) {}

            Property<C> * operator()(ContentProvider & contentProvider) const {
                return constructor(contentProvider);
            }

            bool isValid() const { return constructor != nullptr; }
        };

        /*
         * TODO: Find better solution: Pointer to functor is just crap!
         */
        static const Constructor & getFactoryFor(const std::string & name) {
            const auto & map = getMap();
            const auto & it = map.find(name);

            if (it != map.end())
                return it->second;

            static Constructor invalidValue = Constructor(nullptr);
            return invalidValue;
        }

    protected:
        using MapType = std::unordered_map<std::string, Constructor>;

        // Use this method to save the map to avoid the Static Initialization Order Fiasko.
        static MapType & getMap() noexcept {
            static MapType map;
            return map;
        }

        static void registerFactory(const std::string & name, Property<C> * (*fun)(ContentProvider&)) noexcept {
            getMap()[name] = Constructor(fun);
        }
    };

    namespace Private {
        template<typename PropertyType, typename C>
        Property<C> * createProperty(ContentProvider & contentProvider) {
            return PropertyType::constructFromProvider(contentProvider);
        }
    }

    template<typename PropertyType, typename C>
    class PropertyRegister : private PropertyFactory<C> {
    public:
        explicit PropertyRegister(const std::string & name) noexcept : PropertyFactory<C>() {
            PropertyFactory<C>::registerFactory(name, &Private::createProperty<PropertyType, C>);
        }
    };
}

#endif //PAXENGINE3_PROPERTYFACTORY_H
