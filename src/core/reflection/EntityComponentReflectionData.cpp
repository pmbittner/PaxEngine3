//
// Created by Paul on 13.08.2018.
//

#include <core/reflection/EntityComponentReflectionData.h>
#include <core/entity/EntityComponent.h>

namespace PAX {
    EntityComponentReflectionData::EntityComponentReflectionData() : entityComponentTypeHierarchy(
            Reflection::GetType<EntityComponent>()) {

    }
}