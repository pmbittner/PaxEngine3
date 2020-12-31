//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_WORLD_H
#define PAXENGINE3_WORLD_H

#include <string>
#include <vector>
#include <algorithm>
#include <paxcore/service/Services.h>

#include <polypropylene/property/Entity.h>
#include <polypropylene/prefab/Prefab.h>

#include "../gameentity/GameEntity.h"

#include "paxcore/world/scenegraph/WorldSceneGraph.h"
#include "paxcore/rendering/scenegraph/generators/SceneGraphGenerator.h"

#include <polypropylene/event/EventService.h>
#include <polypropylene/property/EntityManager.h>
#include <paxcore/gameentity/GameEntityIDService.h>
#include "event/GameEntitySpawnedEvent.h"
#include "event/GameEntityDespawnedEvent.h"

namespace PAX {
    class Game;
    class GameEntity;

    class World : public Entity<World> {
        friend class Game;
        friend class GameEntity;

    private:
        bool initialised = false;
        std::string name = "unnamed";
        float z = 0;
        unsigned int dimensions = 2;

        WorldSceneGraph * sceneGraph = nullptr;
        SceneGraphGenerator * sceneGraphGenerator = nullptr;

        GameEntityManager entities;
        GameEntityIDService idService;
        std::map<Tag, std::vector<GameEntity*>> entitiesByTags;

        void registerTagForGameEntity(GameEntity * entity, const Tag & tag);
        void unregisterTagForGameEntity(GameEntity * entity, const Tag & tag);

    public:
        World();
        World(const std::string& name, int dimensions, float z = 0, SceneGraphGenerator * sceneGraphGenerator = nullptr);
        ~World() override;

        /// \param name The name of this WorldLayer functions as an identifier. Therefore it should be unique.
        /// \param dimensions The number of dimenions, this WorldLayer should have (typically 2 or 3).
        /// \param z An index for ordering the layers. Layers with greater z will be rendered behind layers with smaller z.
        /// \param sceneGraphGenerator The generator, that will be used for correctly arranging cameras and graphics components of this layers entities into its scene graph.
        ///                            If this is nullptr, the factory will be queried to create one
        void initialize(const std::string& name, int dimensions, float z = 0, SceneGraphGenerator * sceneGraphGenerator = nullptr);

        PAX_NODISCARD WorldSceneGraph * getSceneGraph() const;
        PAX_NODISCARD SceneGraphGenerator * getSceneGraphGenerator() const;

        PAX_NODISCARD float getZ() const;
        void setZ(float z);

        void spawn(GameEntity *entity);
        void despawn(GameEntity *entity);

        PAX_NODISCARD const std::set<GameEntity*> & getEntities() const;
        PAX_NODISCARD const GameEntityManager & getGameEntityManager() const;
        GameEntityIDService & getGameEntityIDService();
        const std::vector<GameEntity*> & getEntitiesWithTag(const Tag & tag);

        PAX_NODISCARD unsigned int getDimensions() const;
    };

    using WorldPrefab = Prefab<World>;
}

#endif //PAXENGINE3_WORLD_H
