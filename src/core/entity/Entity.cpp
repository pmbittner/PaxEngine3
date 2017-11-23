//
// Created by Paul on 29.04.2017.
//

#include <typeindex>
#include <core/Services.h>
#include "../../../include/core/entity/Entity.h"
#include "../../../include/lib/easylogging++.h"

namespace PAX {
    Entity::Entity(std::string name) {
        _name = name;
        OnParentChanged.add<EventService, &EventService::fire<EntityParentChangedEvent>>(&_localEventService);
    }

    Entity::~Entity() {
        for (std::pair<const std::type_index, void*>& kv : _components[true]) {
            std::vector<EntityComponent*> *vector = static_cast<std::vector<EntityComponent*>*>(kv.second);
            for (EntityComponent* component : *vector) {
                Services::GetEntityComponentService().free(kv.first, component);
            }
        }
        _components[true].clear();

        for (std::pair<const std::type_index, void*>& kv : _components[false]) {
            Services::GetEntityComponentService().free(kv.first, static_cast<EntityComponent*>(kv.second));
        }
        _components[false].clear();

        _components.clear();
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

    std::string Entity::getName() {
        return _name;
    }

    void Entity::setName(std::string name) {
        _name = name;
    }
}