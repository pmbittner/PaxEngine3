//
// Created by paul on 06.01.19.
//

#ifndef PAXENGINE3_PROPERTYCONTAINERPREFAB_H
#define PAXENGINE3_PROPERTYCONTAINERPREFAB_H

#include <paxcore/service/Services.h>

namespace PAX {
    namespace Internal {
        template<class P, class C>
        Property<C> * createProperty() {
            return PropertyContainer<C>::GetPropertyAllocator().template create<P>();
        }
    }

    template<class C>
    class PropertyFactory {
        static std::unordered_map<std::string, Property<C> * (*)()> factories;

    protected:
        static void registerFactory(const std::string & name, Property<C> * (*fun)()) {
            factories[name] = fun;
        }

    public:
        static Property<C> * create(const std::string & name) {
            const auto & it = factories.find(name);
            if (it != factories.end())
                return it->second();
            return nullptr;
        }
    };
    template<class C>
    std::unordered_map<std::string, Property<C> * (*)()> PropertyFactory<C>::factories;

    template<class Prop, class C>
    class PropertyRegister : private PropertyFactory<C> {
    public:
        explicit PropertyRegister(const char* name) : PropertyFactory<C>() {
            PropertyFactory<C>::registerFactory(name, &Internal::createProperty<Prop, C>);
        }
    };

    template<class C>
    class PropertyContainerPrefab {
    private:
        std::vector<std::string> propertyNames;

    public:
        explicit PropertyContainerPrefab(const std::vector<std::string> & propertyTypenames) : propertyNames(propertyTypenames) {

        }

        /// Creates and attaches properties to the given container c.
        /// It is not required, but assumed that c is empty.
        void createProperties(C& c) {
            auto& allocator = PropertyContainer<C>::GetPropertyAllocator();

            for (const std::string & propertyTypename : propertyNames) {
                if (Property<C> * p = PropertyFactory<C>::create(propertyTypename)) {
                    c.add(p);
                }
            }
        }
    };
}

#endif //PAXENGINE3_PROPERTYCONTAINERPREFAB_H
