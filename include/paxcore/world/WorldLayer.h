//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_WORLDLAYER_H
#define PAXENGINE3_WORLDLAYER_H

#include <string>
#include <vector>
#include <algorithm>
#include <paxcore/service/Services.h>

#include <polypropylene/property/Entity.h>

#include "WorldLayerLayout.h"
#include "../gameentity/GameEntity.h"

#include "scenegraph/WorldLayerSceneGraph.h"
#include "paxcore/rendering/scenegraph/generators/SceneGraphGenerator.h"

#include <polypropylene/event/EventService.h>
#include <polypropylene/property/EntityManager.h>
#include <paxcore/gameentity/GameEntityIDService.h>
#include "event/GameEntitySpawnedEvent.h"
#include "event/GameEntityDespawnedEvent.h"

namespace PAX {
    using WorldLayerPrefab = Prefab<WorldLayer>;

    class World;

    class WorldLayer : public Entity<WorldLayer> {
        friend class SceneGraphGenerator;
        friend class World;
        friend class GameEntity;

        std::string name;

        // These should be const, but are not due to being set via initialize method.
        float z = 0;
        int dimensions = -1;

        std::shared_ptr<WorldLayerSceneGraph> sceneGraph;
        std::shared_ptr<SceneGraphGenerator> sceneGraphGenerator;

        GameEntityManager entities;
        GameEntityIDService idService;
        std::map<Tag, std::vector<GameEntity*>> entitiesByTags;

        World * world = nullptr;
        void setWorld(World * world);

        void registerTagForGameEntity(GameEntity * entity, const Tag & tag);
        void unregisterTagForGameEntity(GameEntity * entity, const Tag & tag);

    public:
        WorldLayer();
        /// Calls the initialize method directly.
        WorldLayer(const std::string& name, int dimensions, float z = 0, const std::shared_ptr<SceneGraphGenerator> & sceneGraphGenerator = nullptr);
        ~WorldLayer() override;

        /// \param name The name of this WorldLayer functions as an identifier. Therefore it should be unique.
        /// \param dimensions The number of dimenions, this WorldLayer should have (typically 2 or 3).
        /// \param z An index for ordering the layers. Layers with greater z will be rendered behind layers with smaller z.
        /// \param sceneGraphGenerator The generator, that will be used for correctly arranging cameras and graphics components of this layers entities into its scene graph.
        ///                            If this is nullptr, the factory will be queried to create one
        void initialize(const std::string& name, int dimensions, float z = 0, const std::shared_ptr<SceneGraphGenerator> & sceneGraphGenerator = nullptr);

        void spawn(GameEntity *entity);
        void despawn(GameEntity *entity);

        PAX_NODISCARD const std::set<GameEntity*> & getEntities() const;
        PAX_NODISCARD const GameEntityManager & getGameEntityManager() const;
        GameEntityIDService & getGameEntityIDService();
        const std::vector<GameEntity*> & getEntitiesWithTag(const Tag & tag);

        PAX_NODISCARD const std::string& getName() const;
        PAX_NODISCARD const std::shared_ptr<WorldLayerSceneGraph>& getSceneGraph() const;
        PAX_NODISCARD const std::vector<Camera*> & getCameras() const;
        PAX_NODISCARD World * getWorld() const;

        PAX_NODISCARD int getDimensions() const;

        bool operator<(const WorldLayer & rhs) const;

        PAX_NODISCARD bool isActive() const;
    };

    struct WorldLayerSort {
        bool operator()(WorldLayer * a, WorldLayer * b);
    };

    using WorldLayerManager = EntityManager<WorldLayer>;

    template<typename... RequiredProperties>
    using WorldLayerManagerView = EntityManagerView<WorldLayer, RequiredProperties...>;
}

#endif //PAXENGINE3_WORLDLAYER_H
