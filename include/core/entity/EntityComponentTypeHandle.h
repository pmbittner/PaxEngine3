//
// Created by Paul on 14.01.2018.
//

#ifndef PAXENGINE3_ENTITYCOMPONENTHANDLE_H
#define PAXENGINE3_ENTITYCOMPONENTHANDLE_H

#include <typeindex>

namespace PAX {
    class EntityComponent;

    struct EntityComponentTypeHandle {
        static const std::type_index Root;

        std::type_index type;
        EntityComponentTypeHandle *superType = nullptr;

        EntityComponentTypeHandle(std::type_index type = Root, EntityComponentTypeHandle* superType = nullptr);
        EntityComponentTypeHandle(const EntityComponentTypeHandle& other);

        void operator=(const EntityComponentTypeHandle& other);
    };
}

#endif //PAXENGINE3_ENTITYCOMPONENTHANDLE_H
