//
// Created by Paul on 01.05.2017.
//

#include <paxcore/entity/EntityComponent.h>

namespace PAX {
    EntityComponent::EntityComponent() : _owner(nullptr) {

    }

    EntityComponent::~EntityComponent() {

    }

    void EntityComponent::attached(Entity &entity) {}
    void EntityComponent::detached(Entity &entity) {}

    Entity* EntityComponent::getOwner() const {
        return _owner;
    }

    bool EntityComponent::areDependenciesMetFor(const Entity &entity) const {
        return true;
    }

    bool EntityComponent::isMultiple() const {
        return IsMultiple();
    }
}