//
// Created by Paul on 29.04.2017.
//

#include <typeindex>

#include <paxcore/entity/Entity.h>
#include <paxcore/entity/EntityProperty.h>
#include <paxcore/service/Services.h>
#include <paxcore/world/World.h>

namespace PAX {
    Entity::Entity() = default;
    Entity::~Entity() = default;

    void Entity::updateActiveStatus() {
        bool active = false;
        if (WorldLayer * wl = getWorldLayer()) {
            active = wl->isActive();
        }

        if (active) {
            activate();
        } else {
            deactivate();
        }
    }

    Transformation& Entity::getTransformation() {
        return transform;
    }

    void Entity::setParent(Entity * parent) {
        Entity * oldParent = parent;//#PRANT
        this->parent = parent;

        if (oldParent) {
            Util::removeFromVector(parent->children, this);
        }

        Transformation * parentTransform = nullptr;
        if (parent) {
            parentTransform = &parent->transform;
            parent->children.push_back(this);
        }
        transform.setParent(parentTransform);

        EntityParentChangedEvent e(this, oldParent, parent);
        OnParentChanged(e);
        getEventService()(e);
    }

    Entity* Entity::getParent() const {
        return parent;
    }

    const std::vector<Entity*>& Entity::getChildren() const {
        return children;
    }

    WorldLayer* Entity::getWorldLayer() const {
        return worldLayer;
    }
}