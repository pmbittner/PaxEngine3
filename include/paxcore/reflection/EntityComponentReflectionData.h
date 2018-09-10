//
// Created by Paul on 13.08.2018.
//

#ifndef PAXENGINE3_ENTITYCOMPONENTREFLECTIONDATA_H
#define PAXENGINE3_ENTITYCOMPONENTREFLECTIONDATA_H

#include <paxutil/datastructures/TypeMap.h>
#include <paxutil/reflection/TypeHierarchy.h>

namespace PAX {
    class Entity;
    class EntityComponent;

    struct EntityComponentReflectionData {
        TypeMap<void (*)(Entity*, EntityComponent*)> entityComponentAttachedHandlers;
        TypeMap<void (*)(Entity*, EntityComponent*)> entityComponentDetachedHandlers;
        TypeMap<bool> isMultiple;
        Reflection::TypeHierarchy entityComponentTypeHierarchy;

        EntityComponentReflectionData();
    };
}

#endif //PAXENGINE3_ENTITYCOMPONENTREFLECTIONDATA_H
