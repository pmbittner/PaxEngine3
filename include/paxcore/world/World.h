//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_WORLD_H
#define PAXENGINE3_WORLD_H

#include <vector>
#include "WorldLayerEvent.h"
#include "scenegraph/WorldSceneGraph.h"

namespace PAX {
    class Game;

    class World {
        friend class Game;

    private:
        EventService localEventService;
        WorldSceneGraph sceneGraph;
        PropertyContainerManager<WorldLayer> worldLayers;

        bool active = false;

        void setActive(bool active);

    public:
        World();
        virtual ~World();

        void addLayer(WorldLayer *layer);
        void removeLayer(WorldLayer *layer);
        const std::set<WorldLayer*> & getLayers();
        [[nodiscard]] const PropertyContainerManager<WorldLayer> & getWorldLayerManager() const;
        WorldLayer* getWorldLayerWithName(const std::string& name);

        WorldSceneGraph* getSceneGraph();
        EventService& getEventService();
        [[nodiscard]] bool isActive() const;
    };
}

#endif //PAXENGINE3_WORLD_H
