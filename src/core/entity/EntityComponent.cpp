//
// Created by Paul on 01.05.2017.
//

#include "../../../include/core/entity/EntityComponent.h"

namespace PAX {
    EntityComponent::EntityComponent() : _owner(nullptr) {

    }

    Entity* EntityComponent::getOwner() {
        return _owner;
    }
}