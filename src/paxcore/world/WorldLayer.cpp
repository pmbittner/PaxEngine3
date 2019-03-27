//
// Created by Paul on 08.05.2017.
//

#include <algorithm>
#include <paxcore/world/WorldLayer.h>
#include <paxcore/world/scenegraph/WorldLayerSceneGraphFactory.h>
#include <paxcore/rendering/scenegraph/generators/SceneGraphGeneratorFactory.h>

namespace PAX {
    WorldLayer::WorldLayer(const std::string& name, int dimensions, float z, const std::shared_ptr<SceneGraphGenerator> & sceneGraphGenerator)
    : z(z),
      _name(name),
      _dimensions(dimensions),
      entities(getEventService())
    {
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
        while (!entities.empty()) {
            despawn(*entities.begin());
        }
        _sceneGraphGenerator->terminate(getEventService());
    }

    void WorldLayer::spawn(Entity * entity) {
        assert(entity->_worldLayer == nullptr);

        if (entities.add(entity)) {
            for (Entity *child : entity->getChildren()) {
                spawn(child);
            }

            entity->_worldLayer = this;
            entity->getEventService().setParent(&getEventService());

            EntitySpawnedEvent e(entity);
            getEventService()(e);
        }
    }

    void WorldLayer::despawn(Entity * entity) {
        if (entities.remove(entity)) {
            for (Entity *child : entity->getChildren())
                despawn(child);

            entity->_worldLayer = nullptr;

            EntityDespawnedEvent e(entity, this);
            getEventService()(e);
        }
    }

    const std::set<Entity*>& WorldLayer::getEntities() const {
        return entities.getPropertyContainers();
    }

    const EntityManager & WorldLayer::getEntityManager() const {
        return entities;
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

    bool WorldLayer::operator<(const PAX::WorldLayer &rhs) const {
        return z < rhs.z;
    }

    bool WorldLayerSort::operator()(PAX::WorldLayer *a, PAX::WorldLayer *b) {
        return *a < *b;
    }
}