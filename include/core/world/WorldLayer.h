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
#include "../rendering/scenegraph/SceneGraph.h"
#include "../rendering/scenegraph/SceneGraphGenerator.h"
#include "event/EntitySpawnedEvent.h"
#include "../event/EventListener.h"
#include "event/EntityDespawnedEvent.h"
#include "../event/EventService.h"

namespace PAX {
#define PAX_WORLDLAYERNAME_MAIN "MainLayer"
#define PAX_WORLDLAYERNAME_GUI "GuiLayer"

    class WorldLayer {
        friend class SceneGraphGenerator;

        std::string _name;
        float _z;

        EventService _localEventService;
        WorldLayerLayout *_layout = nullptr;

        SceneGraph *_sceneGraph;
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
        SceneGraph* getSceneGraph();
        EventService& getEventService();
    };
}

#endif //PAXENGINE3_WORLDLAYER_H
