//
// Created by Paul on 08.05.2017.
//

#include <algorithm>
#include <paxcore/world/WorldLayer.h>
#include <paxcore/world/scenegraph/WorldLayerSceneGraphFactory.h>
#include <paxcore/rendering/scenegraph/generators/SceneGraphGeneratorFactory.h>

namespace PAX {
    WorldLayer::WorldLayer(const std::string& name, int dimensions, float z, const std::shared_ptr<SceneGraphGenerator> & sceneGraphGenerator) : _name(name), _dimensions(dimensions) {
        if (sceneGraphGenerator) {
            _sceneGraphGenerator = sceneGraphGenerator;
        } else {
            SceneGraphGeneratorFactory * sceneGraphGeneratorFactory = Services::GetFactoryService().get<SceneGraphGeneratorFactory>();

            if (sceneGraphGeneratorFactory) {
                _sceneGraphGenerator = sceneGraphGeneratorFactory->create(dimensions);
            } else {
                throw std::runtime_error("[WorldLayer::WorldLayer] Could not create SceneGraphGenerator because no factory is registered at the FactoryService!");
            }
        }

        WorldLayerSceneGraphFactory * sceneGraphGeneratorFactory = Services::GetFactoryService().get<WorldLayerSceneGraphFactory>();
        if (sceneGraphGeneratorFactory) {
            _sceneGraph = sceneGraphGeneratorFactory->create(this, z);
        } else {
            throw std::runtime_error("[WorldLayer::WorldLayer] Could not create SceneGraph because no factory is registered at the FactoryService!");
        }

        _sceneGraphGenerator->initialize(_sceneGraph.get(), getEventService());
        _sceneGraph->worldLayer = this;
    }

    WorldLayer::~WorldLayer() {
        while (!_entities.empty()) {
            despawn(_entities.begin());
        }
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
            entity->getEventService().setParent(&getEventService());

            EntitySpawnedEvent e(entity);
            getEventService()(e);
        }
    }

    void WorldLayer::despawn(const std::vector<PAX::Entity *, std::allocator<PAX::Entity *>>::iterator & entityIter) {
        Entity* const entity = *entityIter;

        for (Entity *child : entity->getChildren())
            despawn(child);

        _entities.erase(entityIter);

        entity->_worldLayer = nullptr;
        entity->getEventService().setParent(nullptr);

        EntityDespawnedEvent e(entity, this);
        getEventService()(e);
    }

    void WorldLayer::despawn(Entity *entity) {
        auto entityIter = std::find(_entities.begin(), _entities.end(), entity);
        if (entityIter != _entities.end()) {
            despawn(entityIter);
        }
    }

    const std::vector<Entity*>& WorldLayer::getEntities() const {
        return _entities;
    }

    const std::shared_ptr<WorldLayerSceneGraph>& WorldLayer::getSceneGraph() const {
        return _sceneGraph;
    }

    const std::vector<Camera*>& WorldLayer::getCameras() const {
        return _sceneGraphGenerator->getCameras();
    }

    const std::string& WorldLayer::getName() const {
        return _name;
    }

    int WorldLayer::getDimensions() const {
        return _dimensions;
    }
}