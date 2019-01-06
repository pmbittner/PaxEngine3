//
// Created by Paul on 02.05.2017.
//

#ifndef PAXENGINE3_SCENEGRAPHBUILDER_H
#define PAXENGINE3_SCENEGRAPHBUILDER_H

#include "SceneGraph.h"
#include "../Graphics.h"
#include "../camera/Camera.h"
#include "../../world/event/EntitySpawnedEvent.h"
#include "../../world/event/EntityDespawnedEvent.h"

namespace PAX {
    class SceneGraphGenerator {
        SceneGraph *_root = nullptr;
        std::vector<Camera*> _cameras;

        void addCamera(Camera * g);
        void removeCamera(Camera * g);

    protected:
        SceneGraph sceneRoot;

        virtual void addGraphics(Graphics * g) = 0;
        virtual void removeGraphics(Graphics * g) = 0;

    public:
        SceneGraphGenerator();
        virtual ~SceneGraphGenerator();

        void initialize(SceneGraph *_root, EventService& eventService);

        void onEntitySpawnedEvent(EntitySpawnedEvent& e);
        void onEntityDespawnedEvent(EntityDespawnedEvent& e);
        void onEntityComponentAddedEvent(PropertyAttachedEvent<Entity, Graphics>& e);
        void onEntityComponentRemovedEvent(PropertyDetachedEvent<Entity, Graphics>& e);
        void onEntityComponentAddedEvent(PropertyAttachedEvent<Entity, Camera>& e);
        void onEntityComponentRemovedEvent(PropertyDetachedEvent<Entity, Camera>& e);

        const std::vector<Camera*> & getCameras() const;
    };
}

#endif //PAXENGINE3_SCENEGRAPHBUILDER_H
