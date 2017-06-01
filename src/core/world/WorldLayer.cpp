//
// Created by Paul on 08.05.2017.
//

#include <algorithm>
#include "../../../include/core/world/WorldLayer.h"
#include "../../../include/lib/easylogging++.h"
#include "../../../include/core/world/event/EntitySpawnedEvent.h"
#include "../../../include/core/Engine.h"

namespace PAX {
    WorldLayer::WorldLayer(std::string name, float z) : _name(name), _z(z) {
    }

    void WorldLayer::spawn(Entity *entity) {
        assert(entity->_worldLayer == nullptr);

        auto entityIter = std::find(_entities.begin(), _entities.end(), entity);
        if (entityIter == _entities.end()) {
            _entities.push_back(entity);
            entity->_worldLayer = this;
            entity->_localEventService.setParent(&_localEventService);

            EntitySpawnedEvent e(entity);
            _localEventService(e);
        }
    }

    void WorldLayer::despawn(Entity *entity) {
        auto entityIter = std::find(_entities.begin(), _entities.end(), entity);
        if (entityIter != _entities.end()) {
            _entities.erase(entityIter);
            entity->_worldLayer = nullptr;
            entity->_localEventService.setParent(nullptr);

            EntityDespawnedEvent e(entity);
            _localEventService(e);
        }
    }

    EventService& WorldLayer::getEventService() {
        return _localEventService;
    }

    SceneGraph* WorldLayer::getSceneGraph() {
        return &_sceneGraph;
    }

    std::string WorldLayer::getName() {
        return _name;
    }
}