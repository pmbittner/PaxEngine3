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
        std::unordered_map<std::string, WorldLayer*> _layers;

    public:

        World();
        ~World();

        void addLayer(WorldLayer *layer);
        void removeLayer(WorldLayer *layer);

        WorldLayer* getMainLayer();
        WorldLayer* getGUILayer();
        WorldLayer* getWorldLayerWithName(const std::string& name);

        EventService& getEventService();
    };
}

#endif //PAXENGINE3_WORLD_H
