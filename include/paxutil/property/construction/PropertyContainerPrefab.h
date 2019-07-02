//
// Created by paul on 06.01.19.
//

#ifndef PAXENGINE3_PROPERTYCONTAINERPREFAB_H
#define PAXENGINE3_PROPERTYCONTAINERPREFAB_H

#include "paxutil/StringVariables.h"
#include "paxutil/property/construction/PropertyFactory.h"
#include "paxutil/memory/Allocator.h"

namespace PAX {
    class Prefab {
    public:
        static VariableRegister PreDefinedVariables;
    };

    template<class C>
    class PropertyContainerPrefab : public Prefab {
    protected:
        std::map<Path, std::shared_ptr<PropertyContainerPrefab<C>>> parentPrefabs;

    public:
        explicit PropertyContainerPrefab() = default;
        virtual ~PropertyContainerPrefab() = default;
        virtual C * create(const VariableRegister & variableRegister) = 0;
        virtual void addMyContentTo(C& c, const VariableRegister & variableRegister) = 0;
    };
}

#endif //PAXENGINE3_PROPERTYCONTAINERPREFAB_H
