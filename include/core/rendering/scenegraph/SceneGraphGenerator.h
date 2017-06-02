//
// Created by Paul on 02.05.2017.
//

#ifndef PAXENGINE3_SCENEGRAPHBUILDER_H
#define PAXENGINE3_SCENEGRAPHBUILDER_H

#include "SceneGraph.h"
#include "../Graphics.h"
#include "../Camera.h"
#include "../../world/event/EntitySpawnedEvent.h"
#include "../../world/event/EntityDespawnedEvent.h"
#include "../../entity/event/EntityComponentAddedEvent.h"
#include "../../entity/event/EntityComponentRemovedEvent.h"

namespace PAX {
    class SceneGraphGenerator {
        SceneGraph _sceneRoot;
        SceneGraph *_root;

    public:
        void initialize(SceneGraph *_root, EventService& eventService);

        void onEntitySpawnedEvent(EntitySpawnedEvent& e);
        void onEntityDespawnedEvent(EntityDespawnedEvent& e);
        void onEntityComponentAddedEvent(EntityComponentAddedEvent<Graphics>& e);
        void onEntityComponentRemovedEvent(EntityComponentRemovedEvent<Graphics>& e);
        void onEntityComponentAddedEvent(EntityComponentAddedEvent<Camera>& e);
        void onEntityComponentRemovedEvent(EntityComponentRemovedEvent<Camera>& e);

        void addGraphics(Graphics *g);
        void removeGraphics(Graphics *g);
        void addCamera(Camera *g);
        void removeCamera(Camera *g);
    };
}

#endif //PAXENGINE3_SCENEGRAPHBUILDER_H
