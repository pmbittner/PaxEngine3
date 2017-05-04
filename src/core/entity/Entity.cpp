//
// Created by Paul on 29.04.2017.
//

#include <typeindex>
#include "../../../include/core/entity/Entity.h"
#include "../../../include/lib/easylogging++.h"

namespace PAX {
    Entity::Entity() {

    }

    Entity::~Entity() {

    }

    Transform& Entity::getTransform() {
        return _transform;
    }

    void Entity::setParent(Entity *parent) {
        _parent = parent;
        LOG(WARNING) << "Entity::setParent: event not implemented!";
        Transform *parentTransform = nullptr;
        if (_parent)
            parentTransform = &_parent->_transform;
        _transform.setParent(parentTransform);
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

    //bool Entity::add(EntityComponent *component) {
    //    std::type_index type = std::type_index(typeid(*component));
    //    if (_components.find(type) != _components.end())
    //        _components[type] = component;
    //}
}