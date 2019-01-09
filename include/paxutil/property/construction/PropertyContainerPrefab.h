//
// Created by paul on 06.01.19.
//

#ifndef PAXENGINE3_PROPERTYCONTAINERPREFAB_H
#define PAXENGINE3_PROPERTYCONTAINERPREFAB_H

#include "paxutil/property/construction/PropertyFactory.h"

namespace PAX {
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
