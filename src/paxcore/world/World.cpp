//
// Created by Paul on 28.05.2017.
//

#include <paxcore/world/World.h>
#include <paxcore/Engine.h>
#include <paxcore/Game.h>
#include <paxcore/rendering/scenegraph/generators/SceneGraphGeneratorFactory.h>
#include <paxcore/world/scenegraph/WorldSceneGraphFactory.h>

namespace PAX {
    World::World() : Entity<World>(), entities(getEventService()), initialised(false) {

    }

    World::~World() {
        if (this->sceneGraphGenerator) {
            this->sceneGraphGenerator->terminate(getEventService());
            delete this->sceneGraphGenerator;
        }

        delete this->sceneGraph;

//        while (!entities.empty()) {
//            GameEntity * victim = *entities.begin();
//            despawn(victim);
//            pax_delete(victim);
//        }
//        // should do nothing
//        entities.clear();
    }

    World::World(const std::string &name, int dimensions, float z, SceneGraphGenerator * sceneGraphGenerator)
            : Entity<World>(), entities(getEventService())
    {
        initialize(name, dimensions, z, sceneGraphGenerator);
    }

    void World::initialize(const std::string &name, int dimensions, float z, SceneGraphGenerator * sceneGraphGenerator) {
        if (initialised) {
            PAX_LOG(Log::Level::Warn, "Duplicate Call! Aborting second initialisation.");
            return;
        }

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

        auto * sceneGraphFactory = Services::GetFactoryService().get<WorldSceneGraphFactory>();
        if (sceneGraphFactory) {
            this->sceneGraph = sceneGraphFactory->create(this);
        } else {
            PAX_THROW_RUNTIME_ERROR("[WorldLayer::WorldLayer] Could not create SceneGraph because no factory is registered at the FactoryService!");
        }

        this->sceneGraphGenerator->initialize(this->sceneGraph, getEventService());
        this->sceneGraph->world = this;
        this->sceneGraph->z = z;

        initialised = true;
    }

    WorldSceneGraph* World::getSceneGraph() const {
        return sceneGraph;
    }

    SceneGraphGenerator * World::getSceneGraphGenerator() const {
        return sceneGraphGenerator;
    }

    void World::spawn(GameEntity * entity) {
        assert(entity->world == nullptr);

        if (!idService.hasID(entity)) {
            idService.generateIDFor(entity);
        }

        if (entities.add(entity)) {
            for (GameEntity *child : entity->getChildren()) {
                spawn(child);
            }

            entity->world = this;
            entity->getEventService().setParent(&getEventService());

            for (const Tag & tag : entity->getTags()) {
                registerTagForGameEntity(entity, tag);
            }

            entity->spawned();

            GameEntitySpawnedEvent e(entity);
            getEventService()(e);
        }
    }

    void World::despawn(GameEntity * entity) {
        if (entities.remove(entity)) {
            idService.releaseIDOf(entity);

            for (GameEntity *child : entity->getChildren())
                despawn(child);

            entity->world = nullptr;
            entity->getEventService().setParent(nullptr);

            for (const Tag & tag : entity->getTags()) {
                unregisterTagForGameEntity(entity, tag);
            }

            entity->despawned();

            GameEntityDespawnedEvent e(entity, this);
            getEventService()(e);
        }
    }

    const std::set<GameEntity*>& World::getEntities() const {
        return entities.getEntities();
    }

    const GameEntityManager & World::getGameEntityManager() const {
        return entities;
    }

    GameEntityIDService & World::getGameEntityIDService() {
        return idService;
    }

    const std::vector<GameEntity*> & World::getEntitiesWithTag(const PAX::Tag &tag) {
        return entitiesByTags[tag];
    }

    void World::registerTagForGameEntity(PAX::GameEntity *entity, const PAX::Tag &tag) {
        entitiesByTags[tag].push_back(entity);
    }

    void World::unregisterTagForGameEntity(PAX::GameEntity *entity, const PAX::Tag &tag) {
        std::vector<GameEntity*> & taggies = entitiesByTags[tag];
        auto it = std::find(taggies.begin(), taggies.end(), entity);

        if (it != taggies.end()) {
            taggies.erase(it);
        }
    }

    unsigned int World::getDimensions() const {
        return dimensions;
    }

    float World::getZ() const {
        return sceneGraph->getZ();
    }

    void World::setZ(float z) {
        sceneGraph->z = z;
    }
}