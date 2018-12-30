//
// Created by Paul on 29.04.2017.
//

#include <typeindex>

#include <paxcore/entity/Entity.h>
#include <paxcore/entity/EntityComponent.h>
#include <paxcore/service/Services.h>

#include <easylogging++.h>

namespace PAX {
    Entity::Entity() {
        OnParentChanged.add<EventService, &EventService::fire<EntityParentChangedEvent>>(&getEventService());
    }

    Entity::~Entity() {

    }

    Transformation& Entity::getTransformation() {
        return _transform;
    }

    void Entity::setParent(Entity *parent) {
        Entity *oldParent = _parent;//#PRANT
        _parent = parent;

        if (oldParent) {
            Util::removeFromVector(parent->_children, this);
        }

        Transformation *parentTransform = nullptr;
        if (_parent) {
            parentTransform = &_parent->_transform;
            _parent->_children.push_back(this);
        }
        _transform.setParent(parentTransform);

        EntityParentChangedEvent e(this, oldParent, parent);
        OnParentChanged(e);
    }

    Entity* Entity::getParent() const {
        return _parent;
    }

    const std::vector<Entity*>& Entity::getChildren() const {
        return _children;
    }

    WorldLayer* Entity::getWorldLayer() const {
        return _worldLayer;
    }
}