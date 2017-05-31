//
// Created by Paul on 08.05.2017.
//

#include "../../../../include/core/rendering/scenegraph/SceneGraphBuilder.h"
#include "../../../../include/core/world/WorldLayer.h"
#include "../../../../include/core/Engine.h"
#include <vector>

namespace PAX {
    void SceneGraphBuilder::initialize() {
        EventService *eservice = _worldLayer->getEventService();

        //eservice->add(&onEntitySpawnedEvent);
        //eservice->add(&onEntityDespawnedEvent);
        //eservice->add(&onEntityComponentAddedEvent);
        //eservice->add(&onEntityComponentRemovedEvent);
    }

    void SceneGraphBuilder::addGraphics(Graphics *g) {
        SceneGraph *mySceneGraph = _worldLayer->getSceneGraph();
        SceneGraphBuildingRule *rule = g->getSceneGraphBuildingRule();
        SceneGraph *node = rule->determineSceneGraphNodeFor(g, mySceneGraph);
        node->addRenderable(g);
    }

    void SceneGraphBuilder::removeGraphics(Graphics *g) {

    }

    void SceneGraphBuilder::onEntitySpawnedEvent(EntitySpawnedEvent *e) {
        Entity *entity = e->entity;
        if (entity->has<Graphics>()) {
            const std::vector<Graphics*> &gfx = entity->get<Graphics>();
            for (Graphics *g : gfx)
                addGraphics(g);
        }
    }

    void SceneGraphBuilder::onEntityComponentAddedEvent(EntityComponentAddedEvent<Graphics> *e) {
        addGraphics(e->_component);
    }

    void SceneGraphBuilder::onEntityDespawnedEvent(EntityDespawnedEvent *e) {
        Entity *entity = e->entity;
        if (entity->has<Graphics>()) {
            const std::vector<Graphics*> &gfx = entity->get<Graphics>();
            for (Graphics *g : gfx)
                removeGraphics(g);
        }
    }

    void SceneGraphBuilder::onEntityComponentRemovedEvent(EntityComponentRemovedEvent<Graphics> *e) {
        removeGraphics(e->_component);
    }
}