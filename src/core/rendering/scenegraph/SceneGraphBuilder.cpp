//
// Created by Paul on 08.05.2017.
//

#include "../../../../include/core/rendering/scenegraph/SceneGraphBuilder.h"
#include "../../../../include/core/world/WorldLayer.h"

namespace PAX {
    void SceneGraphBuilder::initialize(SceneGraph *sceneGraph, EventService& eventService) {
        _sceneGraph = sceneGraph;

        eventService.add<EntitySpawnedEvent, SceneGraphBuilder, &SceneGraphBuilder::onEntitySpawnedEvent>(this);
        eventService.add<EntityDespawnedEvent, SceneGraphBuilder, &SceneGraphBuilder::onEntityDespawnedEvent>(this);
        eventService.add<EntityComponentAddedEvent<Graphics>, SceneGraphBuilder, &SceneGraphBuilder::onEntityComponentAddedEvent>(this);
        eventService.add<EntityComponentRemovedEvent<Graphics>, SceneGraphBuilder, &SceneGraphBuilder::onEntityComponentRemovedEvent>(this);
    }

    void SceneGraphBuilder::addGraphics(Graphics *g) {
        SceneGraphBuildingRule *rule = g->getSceneGraphBuildingRule();
        SceneGraph *node = rule->determineSceneGraphNodeFor(g, _sceneGraph);
        node->addRenderable(g);
    }

    void SceneGraphBuilder::removeGraphics(Graphics *g) {

    }

    void SceneGraphBuilder::onEntitySpawnedEvent(EntitySpawnedEvent& e) {
        Entity *entity = e.entity;
        if (entity->has<Graphics>()) {
            const std::vector<Graphics*> &gfx = entity->get<Graphics>();
            for (Graphics *g : gfx)
                addGraphics(g);
        }
    }

    void SceneGraphBuilder::onEntityComponentAddedEvent(EntityComponentAddedEvent<Graphics>& e) {
        addGraphics(e._component);
    }

    void SceneGraphBuilder::onEntityDespawnedEvent(EntityDespawnedEvent& e) {
        Entity *entity = e.entity;
        if (entity->has<Graphics>()) {
            const std::vector<Graphics*> &gfx = entity->get<Graphics>();
            for (Graphics *g : gfx)
                removeGraphics(g);
        }
    }

    void SceneGraphBuilder::onEntityComponentRemovedEvent(EntityComponentRemovedEvent<Graphics>& e) {
        removeGraphics(e._component);
    }
}