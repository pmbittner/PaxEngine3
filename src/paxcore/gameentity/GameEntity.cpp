//
// Created by Paul on 29.04.2017.
//

#include <typeindex>

#include <paxcore/gameentity/GameEntity.h>
#include <paxcore/gameentity/GameEntityProperty.h>
#include <paxcore/service/Services.h>
#include <paxcore/world/World.h>

namespace PAX {
    GameEntity::GameEntity() = default;
    GameEntity::~GameEntity() = default;

    Transformation& GameEntity::getTransformation() {
        return transform;
    }

    void GameEntity::setParent(GameEntity * parent) {
        GameEntity * oldParent = parent;//#PRANT
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

        GameEntityParentChangedEvent e(this, oldParent, parent);
        OnParentChanged(e);
        getEventService()(e);
    }

    GameEntity* GameEntity::getParent() const {
        return parent;
    }

    const std::vector<GameEntity*>& GameEntity::getChildren() const {
        return children;
    }

    WorldLayer* GameEntity::getWorldLayer() const {
        return worldLayer;
    }

    void GameEntity::i_setMotionType(PAX::MotionType motionType) {
        this->motionType = motionType;
    }

    MotionType GameEntity::getMotionType() const {
        return motionType;
    }

    void GameEntity::addTag(const PAX::Tag &tag) {
        tags.push_back(tag);

        if (worldLayer) {
            worldLayer->registerTagForGameEntity(this, tag);
        }
    }

    bool GameEntity::removeTag(const PAX::Tag &tag) {
        auto it = std::find(tags.begin(), tags.end(), tag);

        if (it != tags.end()) {
            tags.erase(it);

            if (worldLayer) {
                worldLayer->unregisterTagForGameEntity(this, tag);
            }

            return true;
        }

        return false;
    }

    bool GameEntity::hasTag(const PAX::Tag &tag) const {
        return std::find(tags.begin(), tags.end(), tag) != tags.end();
    }

    const std::vector<Tag>& GameEntity::getTags() const {
        return tags;
    }

    bool GameEntity::isActive() const {
        return worldLayer ? worldLayer->isActive() : false;
    }
}