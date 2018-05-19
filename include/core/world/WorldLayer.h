//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_WORLDLAYER_H
#define PAXENGINE3_WORLDLAYER_H

#include <string>
#include <vector>
#include <algorithm>
#include <core/service/Services.h>

#include "WorldLayerLayout.h"
#include "../entity/Entity.h"

#include "scenegraph/WorldLayerSceneGraph.h"
#include "../rendering/scenegraph/SceneGraphGenerator.h"

#include "core/event/EventService.h"
#include "event/EntitySpawnedEvent.h"
#include "event/EntityDespawnedEvent.h"

namespace PAX {
#define PAX_WORLDLAYERNAME_MAIN "MainLayer"
#define PAX_WORLDLAYERNAME_GUI "GuiLayer"

    class WorldLayer {
        friend class SceneGraphGenerator;

        std::string _name;

        EventService _localEventService;
        WorldLayerLayout *_layout = nullptr;

        std::shared_ptr<WorldLayerSceneGraph> _sceneGraph;
        std::shared_ptr<SceneGraphGenerator> _sceneGraphGenerator;
        std::vector<Entity*> _entities;

    public:
        WorldLayer(std::string name, float z = 0, std::shared_ptr<SceneGraphGenerator> sceneGraphGenerator = Services::GetFactory().create<SceneGraphGenerator>());
        ~WorldLayer();

        void spawn(Entity *entity);
        void despawn(Entity *entity);

        const std::vector<Entity*>& getEntities();

        std::string getName();
        WorldLayerSceneGraph* getSceneGraph();
        EventService& getEventService();
    };
}

#endif //PAXENGINE3_WORLDLAYER_H
