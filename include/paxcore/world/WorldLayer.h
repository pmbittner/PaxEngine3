//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_WORLDLAYER_H
#define PAXENGINE3_WORLDLAYER_H

#include <string>
#include <vector>
#include <algorithm>
#include <paxcore/service/Services.h>

#include <paxutil/property/PropertyContainer.h>

#include "WorldLayerLayout.h"
#include "../entity/Entity.h"

#include "scenegraph/WorldLayerSceneGraph.h"
#include "paxcore/rendering/scenegraph/generators/SceneGraphGenerator.h"

#include <paxutil/event/EventService.h>
#include <paxutil/property/PropertyContainerManager.h>
#include <paxcore/entity/EntityIDService.h>
#include "event/EntitySpawnedEvent.h"
#include "event/EntityDespawnedEvent.h"

namespace PAX {
    using WorldLayerPrefab = PropertyContainerPrefab<WorldLayer>;

    class World;

    class WorldLayer : public PropertyContainer<WorldLayer> {
        friend class SceneGraphGenerator;
        friend class World;

        std::string name;

        // These should be const, but are not due to being set via initialize method.
        float z = 0;
        int dimensions = -1;

        std::shared_ptr<WorldLayerSceneGraph> sceneGraph;
        std::shared_ptr<SceneGraphGenerator> sceneGraphGenerator;

        EntityManager entities;
        EntityIDService idService;

        World * world = nullptr;

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

        void spawn(Entity *entity);
        void despawn(Entity *entity);

        const std::set<Entity*> & getEntities() const;
        const EntityManager & getEntityManager() const;
        EntityIDService & getEntityIDService();

        const std::string& getName() const;
        const std::shared_ptr<WorldLayerSceneGraph>& getSceneGraph() const;
        const std::vector<Camera*> & getCameras() const;
        World * getWorld() const;

        int getDimensions() const;

        bool operator<(const WorldLayer & rhs) const;
    };

    struct WorldLayerSort {
        bool operator()(WorldLayer * a, WorldLayer * b);
    };

    using WorldLayerManager = PropertyContainerManager<WorldLayer>;

    template<typename... RequiredProperties>
    using WorldLayerManagerView = PropertyContainerManagerView<WorldLayer, RequiredProperties...>;
}

#endif //PAXENGINE3_WORLDLAYER_H
