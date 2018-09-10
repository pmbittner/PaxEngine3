//
// Created by Paul on 13.08.2018.
//

#include <paxcore/reflection/EntityComponentReflectionData.h>
#include <paxcore/entity/EntityComponent.h>

namespace PAX {
    EntityComponentReflectionData::EntityComponentReflectionData() : entityComponentTypeHierarchy(
            Reflection::GetType<EntityComponent>()) {

    }
}