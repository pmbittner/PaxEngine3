//
// Created by paul on 06.01.19.
//

#ifndef PAXENGINE3_PROPERTYCONTAINERPREFAB_H
#define PAXENGINE3_PROPERTYCONTAINERPREFAB_H

#include "paxutil/property/construction/PropertyFactory.h"

namespace PAX {
    template<class C>
    class PropertyContainerPrefab {
    public:
        virtual ~PropertyContainerPrefab() = 0;
        virtual std::shared_ptr<C> create() = 0;
    };
}

#endif //PAXENGINE3_PROPERTYCONTAINERPREFAB_H
