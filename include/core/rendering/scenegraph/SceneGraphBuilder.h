//
// Created by Paul on 02.05.2017.
//

#ifndef PAXENGINE3_SCENEGRAPHBUILDER_H
#define PAXENGINE3_SCENEGRAPHBUILDER_H

#include "../Graphics.h"
#include "../../world/event/EntitySpawnedEvent.h"
#include "../../world/event/EntityDespawnedEvent.h"
#include "../../entity/event/EntityComponentAddedEvent.h"
#include "../../entity/event/EntityComponentRemovedEvent.h"

namespace PAX {
    class SceneGraphBuilder {
        SceneGraph *_sceneGraph = nullptr;

    public:
        void initialize(SceneGraph *sceneGraph, EventService& eventService);

        void onEntitySpawnedEvent(EntitySpawnedEvent& e);
        void onEntityDespawnedEvent(EntityDespawnedEvent& e);
        void onEntityComponentAddedEvent(EntityComponentAddedEvent<Graphics>& e);
        void onEntityComponentRemovedEvent(EntityComponentRemovedEvent<Graphics>& e);

        void addGraphics(Graphics *g);
        void removeGraphics(Graphics *g);
    };
}

#endif //PAXENGINE3_SCENEGRAPHBUILDER_H
