//
// Created by Paul on 02.05.2017.
//

#ifndef PAXENGINE3_SCENEGRAPHBUILDER_H
#define PAXENGINE3_SCENEGRAPHBUILDER_H

#include "paxcore/rendering/scenegraph/SceneGraph.h"
#include "paxcore/rendering/Graphics.h"
#include "paxcore/rendering/camera/Camera.h"
#include "paxcore/world/event/GameEntitySpawnedEvent.h"
#include "paxcore/world/event/GameEntityDespawnedEvent.h"

namespace PAX {
    class RenderPass;

    class SceneGraphGenerator {
        SceneGraph * targetRoot = nullptr;
        std::vector<Camera*> cameras;
        std::vector<RenderPass*> renderPasses;

        void addCamera(Camera * g);
        void removeCamera(Camera * g);

    protected:
        SceneGraph sceneRoot;
        SceneGraph cameraChild;

        virtual void addGraphics(Graphics * g) = 0;
        virtual void removeGraphics(Graphics * g) = 0;

    public:
        SceneGraphGenerator();
        virtual ~SceneGraphGenerator();

        void initialize(SceneGraph *_root, EventService& eventService);
        void terminate(EventService& eventService);

        void onGameEntitySpawnedEvent(GameEntitySpawnedEvent& e);
        void onGameEntityDespawnedEvent(GameEntityDespawnedEvent& e);
        void onGameEntityComponentAddedEvent(PropertyAttachedEvent<GameEntity, Graphics>& e);
        void onGameEntityComponentRemovedEvent(PropertyDetachedEvent<GameEntity, Graphics>& e);
        void onGameEntityComponentAddedEvent(PropertyAttachedEvent<GameEntity, Camera>& e);
        void onGameEntityComponentRemovedEvent(PropertyDetachedEvent<GameEntity, Camera>& e);

        PAX_NODISCARD const std::vector<Camera*> & getCameras() const;

        void addRenderPass(RenderPass * renderPass);
        PAX_NODISCARD const std::vector<RenderPass*> & getRenderPasses() const;
    };
}

#endif //PAXENGINE3_SCENEGRAPHBUILDER_H
