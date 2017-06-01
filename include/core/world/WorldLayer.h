//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_WORLDLAYER_H
#define PAXENGINE3_WORLDLAYER_H

#include <string>
#include <vector>
#include <algorithm>
#include "WorldLayerLayout.h"
#include "../entity/Entity.h"
#include "../rendering/scenegraph/SceneGraph.h"
#include "event/EntitySpawnedEvent.h"
#include "../event/EventListener.h"
#include "event/EntityDespawnedEvent.h"
#include "../event/EventService.h"

namespace PAX {
#define PAX_WORLDLAYERNAME_MAIN "MainLayer"
#define PAX_WORLDLAYERNAME_GUI "GuiLayer"
#define PAX_WORLDLAYERNAME_BACKGROUND "Background"

    class WorldLayer {
        friend class SceneGraphBuilder;

    private:
        std::string _name;
        float _z;

        EventService _localEventService;
        WorldLayerLayout *_layout = nullptr;

        SceneGraph _sceneGraph;
        SceneGraphBuilder _sceneGraphBuilder;

        std::vector<Entity*> _entities;

    public:
        WorldLayer(std::string name = PAX_WORLDLAYERNAME_MAIN, float z = 0);

        void spawn(Entity *entity);
        void despawn(Entity *entity);

        std::string getName();
        SceneGraph* getSceneGraph();
        EventService& getEventService();
    };
}

#endif //PAXENGINE3_WORLDLAYER_H
