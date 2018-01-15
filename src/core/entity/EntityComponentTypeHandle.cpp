//
// Created by Paul on 14.01.2018.
//

#include <core/entity/EntityComponentTypeHandle.h>
#include <core/entity/EntityComponent.h>

namespace PAX {
    const std::type_index EntityComponentTypeHandle::Root = typeid(EntityComponent);

    EntityComponentTypeHandle::EntityComponentTypeHandle(std::type_index type, EntityComponentTypeHandle* superType) : type(type), superType(superType) {

    }

    EntityComponentTypeHandle::EntityComponentTypeHandle(const EntityComponentTypeHandle &other) : type(other.type), superType(other.superType) {

    }

    void EntityComponentTypeHandle::operator=(const EntityComponentTypeHandle &other) {
        type = other.type;
        superType = other.superType;
    }
}