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

    protected:
        SceneGraph _sceneRoot;
        std::vector<std::shared_ptr<Camera>> _cameras;

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

        void addCamera(const std::shared_ptr<Camera> & g);
        void removeCamera(const std::shared_ptr<Camera> & g);

        const std::vector<std::shared_ptr<Camera>> & getCameras() const;

        virtual void addGraphics(const std::shared_ptr<Graphics> & g) = 0;
        virtual void removeGraphics(const std::shared_ptr<Graphics> & g) = 0;
    };
}

#endif //PAXENGINE3_SCENEGRAPHBUILDER_H
