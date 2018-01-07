//
// Created by Paul on 08.05.2017.
//

#include <algorithm>
#include "../../../include/core/world/WorldLayer.h"
#include "../../../include/core/Engine.h"

namespace PAX {
    WorldLayer::WorldLayer(std::string name, float z, SceneGraphGenerator *sceneGraphGenerator) : _name(name), _sceneGraphGenerator(sceneGraphGenerator) {
        assert(sceneGraphGenerator);
        _sceneGraph = Services::GetRenderFactory()->createSceneGraphNodeFor(this, z);
        _sceneGraphGenerator->initialize(_sceneGraph, _localEventService);
    }

    WorldLayer::~WorldLayer() {
        delete _sceneGraphGenerator;
    }

    void WorldLayer::spawn(Entity *entity) {
        assert(entity->_worldLayer == nullptr);

        auto entityIter = std::find(_entities.begin(), _entities.end(), entity);
        if (entityIter == _entities.end()) {
            for (Entity *child : entity->getChildren()) {
                spawn(child);
            }

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
            for (Entity *child : entity->getChildren())
                despawn(child);

            _entities.erase(entityIter);

            entity->_worldLayer = nullptr;
            entity->_localEventService.setParent(nullptr);

            EntityDespawnedEvent e(entity);
            _localEventService(e);
        }
    }

    const std::vector<Entity*>& WorldLayer::getEntities() {
        return _entities;
    }

    EventService& WorldLayer::getEventService() {
        return _localEventService;
    }

    WorldLayerSceneGraph* WorldLayer::getSceneGraph() {
        return _sceneGraph;
    }

    std::string WorldLayer::getName() {
        return _name;
    }
}