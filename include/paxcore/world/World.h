//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_WORLD_H
#define PAXENGINE3_WORLD_H

#include <vector>
#include "WorldLayer.h"
#include "scenegraph/WorldSceneGraph.h"

namespace PAX {
    class World;
    class Game;

    struct WorldLayerEvent : public Event {
        World * world;
        WorldLayer * worldLayer;

        WorldLayerEvent(World * world, WorldLayer * worldLayer);
    };

    struct WorldLayerAddedEvent : public WorldLayerEvent {
        WorldLayerAddedEvent(World * world, WorldLayer * worldLayer);
    };

    struct WorldLayerRemovedEvent : public WorldLayerEvent {
        WorldLayerRemovedEvent(World * world, WorldLayer * worldLayer);
    };

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
        const PropertyContainerManager<WorldLayer> & getWorldLayerManager() const;
        WorldLayer* getWorldLayerWithName(const std::string& name);

        WorldSceneGraph* getSceneGraph();
        EventService& getEventService();
        bool isActive() const;
    };
}

#endif //PAXENGINE3_WORLD_H
