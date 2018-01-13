//
// Created by Paul on 29.04.2017.
//

#include <typeindex>
#include <core/service/Services.h>
#include "../../../include/core/entity/Entity.h"
#include "../../../include/lib/easylogging++.h"

namespace PAX {
    const std::vector<EntityComponent*> Entity::EmptyEntityComponentVector(0);

    Entity::Entity() {
        OnParentChanged.add<EventService, &EventService::fire<EntityParentChangedEvent>>(&_localEventService);
    }

    Entity::~Entity() {
        for (std::pair<const std::type_index, std::vector<EntityComponent*>>& kv : _multipleComponents) {
            for (EntityComponent* component : kv.second) {
                Services::GetEntityComponentService().free(kv.first, component);
            }
        }

        for (std::pair<const std::type_index, EntityComponent*>& kv : _singleComponents) {
            Services::GetEntityComponentService().free(kv.first, kv.second);
        }

        _multipleComponents.clear();
        _singleComponents.clear();
    }

    Transform& Entity::getTransform() {
        return _transform;
    }

    void Entity::setParent(Entity *parent) {
        Entity *oldParent = _parent;//#PRANT
        _parent = parent;

        if (oldParent) {
            Util::removeFromVector(parent->_children, this);
        }

        Transform *parentTransform = nullptr;
        if (_parent) {
            parentTransform = &_parent->_transform;
            _parent->_children.push_back(this);
        }
        _transform.setParent(parentTransform);

        EntityParentChangedEvent e(this, oldParent, parent);
        OnParentChanged(e);
    }

    Entity* Entity::getParent() {
        return _parent;
    }

    const std::vector<Entity*>& Entity::getChildren() {
        return _children;
    }

    WorldLayer* Entity::getWorldLayer() {
        return _worldLayer;
    }

    EventService& Entity::getEventService() {
        return _localEventService;
    }

    template <>
    bool Entity::checkDependencies(EntityComponentProperties<PAX::EntityComponent> &properties, Entity* entity) {
        return true;
    }

    template<>
    bool Entity::addComponentAsAllOfItsTypes(EntityComponent* component, const EntityComponentProperties<EntityComponent> &properties) {
        return true;
    }

    template <>
    bool Entity::removeComponentAsAllOfItsTypes(EntityComponent* component, const EntityComponentProperties<EntityComponent> &properties) {
        return true;
    }
}