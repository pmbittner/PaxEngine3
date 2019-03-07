//
// Created by paul on 06.01.19.
//

#ifndef PAXENGINE3_PROPERTYCONTAINERPREFAB_H
#define PAXENGINE3_PROPERTYCONTAINERPREFAB_H

#include "paxutil/StringVariables.h"
#include "paxutil/property/construction/PropertyFactory.h"

namespace PAX {
    template<class C>
    class PropertyContainerPrefab {
    protected:
        std::map<Path, std::shared_ptr<PropertyContainerPrefab<C>>> parentPrefabs;

    public:
        static VariableRegister PreDefinedVariables;

        virtual ~PropertyContainerPrefab() = default;
        virtual std::shared_ptr<C> create() = 0;
        virtual void addMyContentTo(C& c) = 0;
    };

    template<class C>
    VariableRegister PropertyContainerPrefab<C>::PreDefinedVariables;
}

#endif //PAXENGINE3_PROPERTYCONTAINERPREFAB_H
