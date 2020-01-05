//
// Created by Paul on 08.05.2017.
//

#include <algorithm>
#include <paxcore/world/WorldLayer.h>
#include <paxcore/world/scenegraph/WorldLayerSceneGraphFactory.h>
#include <paxcore/rendering/scenegraph/generators/SceneGraphGeneratorFactory.h>

#include <paxcore/world/World.h>

namespace PAX {
    WorldLayer::WorldLayer()
    : entities(getEventService())
    {
    }

    WorldLayer::WorldLayer(const std::string &name, int dimensions, float z,
                           const std::shared_ptr<PAX::SceneGraphGenerator> &sceneGraphGenerator)
            : entities(getEventService())
    {
        initialize(name, dimensions, z, sceneGraphGenerator);
    }

    void WorldLayer::initialize(const std::string &name, int dimensions, float z,
                                const std::shared_ptr<PAX::SceneGraphGenerator> &sceneGraphGenerator) {
        this->z = z;
        this->name = name;
        this->dimensions = dimensions;

        if (sceneGraphGenerator) {
            this->sceneGraphGenerator = sceneGraphGenerator;
        } else {
            auto * sceneGraphGeneratorFactory = Services::GetFactoryService().get<SceneGraphGeneratorFactory>();

            if (sceneGraphGeneratorFactory) {
                this->sceneGraphGenerator = sceneGraphGeneratorFactory->create(dimensions);
            } else {
                PAX_THROW_RUNTIME_ERROR("Could not create SceneGraphGenerator because no factory is registered at the FactoryService!");
            }
        }

        auto * sceneGraphGeneratorFactory = Services::GetFactoryService().get<WorldLayerSceneGraphFactory>();
        if (sceneGraphGeneratorFactory) {
            this->sceneGraph = sceneGraphGeneratorFactory->create(this, z);
        } else {
            PAX_THROW_RUNTIME_ERROR("[WorldLayer::WorldLayer] Could not create SceneGraph because no factory is registered at the FactoryService!");
        }

        this->sceneGraphGenerator->initialize(this->sceneGraph.get(), getEventService());
        this->sceneGraph->worldLayer = this;
    }

    WorldLayer::~WorldLayer() {
        while (!entities.empty()) {
            GameEntity * entityToRemove = *entities.begin();
            despawn(entityToRemove);
            // TODO: We have to check what to do here with the entities here!
            //       Otherwise we may have leaked all or most of them!
            //       On the other hand, deleting them may invalidate external references and makes reusing even harder
            //       as these entities would have to be despawned manually at first.
            //delete entityToRemove;
        }

        this->sceneGraphGenerator->terminate(getEventService());
    }

    void WorldLayer::spawn(GameEntity * entity) {
        assert(entity->worldLayer == nullptr);

        if (!idService.hasID(entity)) {
            idService.generateIDFor(entity);
        }

        if (entities.add(entity)) {
            for (GameEntity *child : entity->getChildren()) {
                spawn(child);
            }

            entity->worldLayer = this;
            entity->getEventService().setParent(&getEventService());

            for (const Tag & tag : entity->getTags()) {
                registerTagForGameEntity(entity, tag);
            }

            entity->spawned();

            GameEntitySpawnedEvent e(entity);
            getEventService()(e);
        }
    }

    void WorldLayer::despawn(GameEntity * entity) {
        if (entities.remove(entity)) {
            idService.releaseIDOf(entity);

            for (GameEntity *child : entity->getChildren())
                despawn(child);

            entity->worldLayer = nullptr;
            entity->getEventService().setParent(nullptr);

            for (const Tag & tag : entity->getTags()) {
                unregisterTagForGameEntity(entity, tag);
            }

            entity->despawned();

            GameEntityDespawnedEvent e(entity, this);
            getEventService()(e);
        }
    }

    const std::set<GameEntity*>& WorldLayer::getEntities() const {
        return entities.getEntities();
    }

    const GameEntityManager & WorldLayer::getGameEntityManager() const {
        return entities;
    }

    GameEntityIDService & WorldLayer::getGameEntityIDService() {
        return idService;
    }

    const std::vector<GameEntity*> & WorldLayer::getEntitiesWithTag(const PAX::Tag &tag) {
        return entitiesByTags[tag];
    }

    const std::shared_ptr<WorldLayerSceneGraph>& WorldLayer::getSceneGraph() const {
        return sceneGraph;
    }

    const std::vector<Camera*>& WorldLayer::getCameras() const {
        return sceneGraphGenerator->getCameras();
    }

    const std::string& WorldLayer::getName() const {
        return name;
    }

    void WorldLayer::setWorld(PAX::World * world) {
        this->world = world;
    }

    World* WorldLayer::getWorld() const {
        return world;
    }

    int WorldLayer::getDimensions() const {
        return dimensions;
    }

    void WorldLayer::registerTagForGameEntity(PAX::GameEntity *entity, const PAX::Tag &tag) {
        entitiesByTags[tag].push_back(entity);
    }

    void WorldLayer::unregisterTagForGameEntity(PAX::GameEntity *entity, const PAX::Tag &tag) {
        std::vector<GameEntity*> & taggies = entitiesByTags[tag];
        auto it = std::find(taggies.begin(), taggies.end(), entity);

        if (it != taggies.end()) {
            taggies.erase(it);
        }
    }

    bool WorldLayer::operator<(const PAX::WorldLayer &rhs) const {
        return z < rhs.z;
    }

    bool WorldLayerSort::operator()(PAX::WorldLayer *a, PAX::WorldLayer *b) {
        return *a < *b;
    }

    bool WorldLayer::isActive() const {
        return world ? world->isActive() : false;
    }
}