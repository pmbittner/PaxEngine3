//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_WORLD_H
#define PAXENGINE3_WORLD_H

#include <vector>
#include "WorldLayer.h"

namespace PAX {
    class World {
    private:
        EventService _localEventService;
        std::unordered_map<std::string, WorldLayer*> _layersByName;
        std::vector<WorldLayer*> _layers;
        SceneGraph *_sceneGraph = nullptr;

    public:

        World();
        ~World();

        void addLayer(WorldLayer *layer);
        void removeLayer(WorldLayer *layer);
        const std::vector<WorldLayer*>& getLayers();

        WorldLayer* getMainLayer();
        WorldLayer* getGUILayer();
        WorldLayer* getWorldLayerWithName(const std::string& name);

        SceneGraph* getSceneGraph();

        EventService& getEventService();
    };
}

#endif //PAXENGINE3_WORLD_H
