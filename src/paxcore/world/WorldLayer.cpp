//
// Created by Paul on 08.05.2017.
//

#include <algorithm>
#include <paxcore/world/WorldLayer.h>

namespace PAX {
    WorldLayer::WorldLayer(const std::string& name, int dimensions, float z, std::shared_ptr<SceneGraphGenerator> sceneGraphGenerator) : _name(name), _dimensions(dimensions) {
        if (!sceneGraphGenerator)
            sceneGraphGenerator = Services::GetFactory().create<SceneGraphGenerator>(dimensions);

        _sceneGraphGenerator = sceneGraphGenerator;
        _sceneGraph = Services::GetFactory().create<WorldLayerSceneGraph>(this, z);
        _sceneGraphGenerator->initialize(_sceneGraph.get(), getEventService());

        _sceneGraph->worldLayer = this;
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
            entity->getEventService().setParent(&getEventService());

            EntitySpawnedEvent e(entity);
            getEventService()(e);
        }
    }

    void WorldLayer::despawn(Entity *entity) {
        auto entityIter = std::find(_entities.begin(), _entities.end(), entity);
        if (entityIter != _entities.end()) {
            for (Entity *child : entity->getChildren())
                despawn(child);

            _entities.erase(entityIter);

            entity->_worldLayer = nullptr;
            entity->getEventService().setParent(nullptr);

            EntityDespawnedEvent e(entity, this);
            getEventService()(e);
        }
    }

    const std::vector<Entity*>& WorldLayer::getEntities() const {
        return _entities;
    }

    const std::shared_ptr<WorldLayerSceneGraph>& WorldLayer::getSceneGraph() const {
        return _sceneGraph;
    }

    const std::vector<std::shared_ptr<Camera>>& WorldLayer::getCameras() const {
        return _sceneGraphGenerator->getCameras();
    }

    const std::string& WorldLayer::getName() const {
        return _name;
    }

    int WorldLayer::getDimensions() const {
        return _dimensions;
    }
}