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

#include "../event/EventService.h"
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

        WorldLayerSceneGraph *_sceneGraph;
        SceneGraphGenerator *_sceneGraphGenerator;
        std::vector<Entity*> _entities;

    public:
        WorldLayer();
        WorldLayer(std::string name, float z = 0, SceneGraphGenerator *sceneGraphGenerator = Services::GetRenderFactory()->createDefaultSceneGraphGenerator());
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
