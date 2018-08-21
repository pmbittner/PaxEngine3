//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_WORLD_H
#define PAXENGINE3_WORLD_H

#include <vector>
#include "WorldLayer.h"
#include "scenegraph/WorldSceneGraph.h"

namespace PAX {
    class World {
    private:
        EventService _localEventService;
        std::unordered_map<std::string, WorldLayer*> _layersByName;
        std::vector<WorldLayer*> _layers;
        WorldSceneGraph _sceneGraph;

    public:
        World();
        ~World();

        void addLayer(WorldLayer *layer);
        void removeLayer(WorldLayer *layer);
        const std::vector<WorldLayer*>& getLayers();
        WorldLayer* getWorldLayerWithName(const std::string& name);

        WorldSceneGraph* getSceneGraph();

        EventService& getEventService();
    };
}

#endif //PAXENGINE3_WORLD_H
