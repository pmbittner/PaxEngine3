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
#include "../rendering/scenegraph/SceneGraphGenerator.h"

#include <paxutil/event/EventService.h>
#include "event/EntitySpawnedEvent.h"
#include "event/EntityDespawnedEvent.h"

namespace PAX {
    class WorldLayer : public PropertyContainer<WorldLayer> {
        friend class SceneGraphGenerator;

        std::string _name;
        const int _dimensions;

        std::shared_ptr<WorldLayerSceneGraph> _sceneGraph;
        std::shared_ptr<SceneGraphGenerator> _sceneGraphGenerator;
        std::vector<Entity*> _entities;

        void despawn(const std::vector<Entity*>::iterator&);

    public:
        /// \param name The name of this WorldLayer functions as an identifier. Therefore it should be unique.
        /// \param dimensions The number of dimenions, this WorldLayer should have (typically 2 or 3).
        /// \param z An index for ordering the layers. Layers with greater z will be rendered behind layers with smaller z.
        /// \param sceneGraphGenerator The generator, that will be used for correctly arranging cameras and graphics components of this layers entities into its scene graph.
        ///                            If this is nullptr, the factory will be queried to create one (Services
        WorldLayer(const std::string& name, int dimensions, float z = 0, std::shared_ptr<SceneGraphGenerator> sceneGraphGenerator = nullptr);
        virtual ~WorldLayer();

        void spawn(Entity *entity);
        void despawn(Entity *entity);

        const std::vector<Entity*>& getEntities() const;

        const std::string& getName() const;
        const std::shared_ptr<WorldLayerSceneGraph>& getSceneGraph() const;
        const std::vector<Camera*> & getCameras() const;
        //EventService& getEventService();

        int getDimensions() const;
    };
}

#endif //PAXENGINE3_WORLDLAYER_H
