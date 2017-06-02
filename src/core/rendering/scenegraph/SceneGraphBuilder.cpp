//
// Created by Paul on 08.05.2017.
//

#include "../../../../include/core/rendering/scenegraph/SceneGraphBuilder.h"
#include "../../../../include/core/world/WorldLayer.h"

namespace PAX {
    void SceneGraphBuilder::initialize(EventService& eventService) {
        eventService.add<EntitySpawnedEvent, SceneGraphBuilder, &SceneGraphBuilder::onEntitySpawnedEvent>(this);
        eventService.add<EntityDespawnedEvent, SceneGraphBuilder, &SceneGraphBuilder::onEntityDespawnedEvent>(this);
        eventService.add<EntityComponentAddedEvent<Graphics>, SceneGraphBuilder, &SceneGraphBuilder::onEntityComponentAddedEvent>(this);
        eventService.add<EntityComponentRemovedEvent<Graphics>, SceneGraphBuilder, &SceneGraphBuilder::onEntityComponentRemovedEvent>(this);
        eventService.add<EntityComponentAddedEvent<Camera>, SceneGraphBuilder, &SceneGraphBuilder::onEntityComponentAddedEvent>(this);
        eventService.add<EntityComponentRemovedEvent<Camera>, SceneGraphBuilder, &SceneGraphBuilder::onEntityComponentRemovedEvent>(this);
    }

    void SceneGraphBuilder::addGraphics(Graphics *g) {
        SceneGraph *sceneGraph = (g->getOwner()->getWorldLayer()->getSceneGraph());
        SceneGraphBuildingRule *rule = g->getSceneGraphBuildingRule();
        SceneGraph *node = rule->determineSceneGraphNodeFor(g, sceneGraph);
        node->addRenderable(g);
    }

    void SceneGraphBuilder::removeGraphics(Graphics *g) {

    }

    void SceneGraphBuilder::onEntitySpawnedEvent(EntitySpawnedEvent& e) {
        Entity *entity = e.entity;
        if (entity->has<Graphics>()) {
            addGraphics(entity->get<Graphics>());
        }
    }

    void SceneGraphBuilder::onEntityComponentAddedEvent(EntityComponentAddedEvent<Graphics>& e) {
        addGraphics(e._component);
    }

    void SceneGraphBuilder::onEntityDespawnedEvent(EntityDespawnedEvent& e) {
        Entity *entity = e.entity;
        if (entity->has<Graphics>()) {
            removeGraphics(entity->get<Graphics>());
        }
    }

    void SceneGraphBuilder::onEntityComponentRemovedEvent(EntityComponentRemovedEvent<Graphics>& e) {
        removeGraphics(e._component);
    }

    void SceneGraphBuilder::onEntityComponentAddedEvent(EntityComponentAddedEvent<Camera> &e) {

    }

    void SceneGraphBuilder::onEntityComponentRemovedEvent(EntityComponentRemovedEvent<Camera> &e) {

    }
}