//
// Created by paul on 22.09.18.
//

#ifndef PAXENGINE3_PROPERTYREFLECTIONDATA_H
#define PAXENGINE3_PROPERTYREFLECTIONDATA_H

#include <memory>

#include "../datastructures/TypeMap.h"
#include "../reflection/TypeHierarchy.h"

namespace PAX {
    template<class Container>
    class Property;

    template<class Container>
    struct PropertyReflectionData {
        // Assume Container is subclass of PropertyContainer<Container>
        TypeMap<void (*)(Container*, const std::shared_ptr<Property<Container>>&)> propertyAttachedHandlers;
        TypeMap<void (*)(Container*, const std::shared_ptr<Property<Container>>&)> propertyDetachedHandlers;
        TypeMap<bool> isMultiple;
        Reflection::TypeHierarchy propertyTypeHierarchy;

        PropertyReflectionData() : propertyTypeHierarchy(Reflection::GetType<Property<Container>>()) {

        }
    };
}

#endif //PAXENGINE3_PROPERTYREFLECTIONDATA_H
