//
// Created by Paul on 08.05.2017.
//

#include <algorithm>
#include <core/world/WorldLayer.h>

namespace PAX {
    WorldLayer::WorldLayer(const std::string& name, int dimensions, float z, std::shared_ptr<SceneGraphGenerator> sceneGraphGenerator) : _name(name), _dimensions(dimensions) {
        if (!sceneGraphGenerator)
            sceneGraphGenerator = Services::GetFactory().create<SceneGraphGenerator>(dimensions);
        _sceneGraphGenerator = sceneGraphGenerator;
        _sceneGraph = Services::GetFactory().create<WorldLayerSceneGraph>(this, z);
        _sceneGraphGenerator->initialize(_sceneGraph.get(), _localEventService);
    }

    WorldLayer::~WorldLayer() {}

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
        // Fixme: May be wrong for now, but I am a noob with shared pointers.
        return _sceneGraph.get();
    }

    std::string WorldLayer::getName() {
        return _name;
    }
}