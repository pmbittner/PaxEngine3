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

    void Entity::i_setMotionType(PAX::MotionType motionType) {
        this->motionType = motionType;
    }

    MotionType Entity::getMotionType() const {
        return motionType;
    }

    void Entity::addTag(const PAX::Tag &tag) {
        tags.push_back(tag);

        if (worldLayer) {
            worldLayer->registerTagForEntity(this, tag);
        }
    }

    bool Entity::removeTag(const PAX::Tag &tag) {
        auto it = std::find(tags.begin(), tags.end(), tag);

        if (it != tags.end()) {
            tags.erase(it);

            if (worldLayer) {
                worldLayer->unregisterTagForEntity(this, tag);
            }

            return true;
        }

        return false;
    }

    bool Entity::hasTag(const PAX::Tag &tag) const {
        return std::find(tags.begin(), tags.end(), tag) != tags.end();
    }

    const std::vector<Tag>& Entity::getTags() const {
        return tags;
    }
}