//
// Created by paul on 06.01.19.
//

#ifndef PAXENGINE3_PROPERTYFACTORY_H
#define PAXENGINE3_PROPERTYFACTORY_H

#include <string>
#include <unordered_map>

namespace PAX {
    namespace Internal {
        template<class P, class C>
        Property<C> * createProperty() {
            return PropertyContainer<C>::GetPropertyAllocator().template create<P>();
        }
    }

    template<class C>
    class PropertyFactory {
    public:
        using MapType = std::unordered_map<std::string, Property<C> * (*)()>;

        // Use this method to save the map to avoid the Static Initialization Order Fiasko.
        static MapType & getMap() {
            static MapType map;
            return map;
        }

        static Property<C> * create(const std::string & name) {
            const auto & map = getMap();
            const auto & it = map.find(name);
            if (it != map.end())
                return it->second();
            return nullptr;
        }

    protected:
        static void registerFactory(const std::string & name, Property<C> * (*fun)()) {
            getMap()[name] = fun;
        }
    };

    template<class Prop, class C>
    class PropertyRegister : private PropertyFactory<C> {
    public:
        explicit PropertyRegister(const std::string & name) : PropertyFactory<C>() {
            PropertyFactory<C>::registerFactory(name, &Internal::createProperty<Prop, C>);
        }
    };
}

#endif //PAXENGINE3_PROPERTYFACTORY_H
