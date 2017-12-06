//
// Created by Paul on 08.05.2017.
//

#include "../../../../include/core/rendering/scenegraph/SceneGraphGenerator.h"
#include "../../../../include/core/world/WorldLayer.h"
#include "utility/macros/MacroIncludes.h"

namespace PAX {
    SceneGraphGenerator::SceneGraphGenerator() {}
    SceneGraphGenerator::~SceneGraphGenerator() {}

    void SceneGraphGenerator::initialize(SceneGraph* root, EventService& eventService) {
        PAX_assertNotNull(root, "Root can't be null!");
        _root = root;

        eventService.add<EntitySpawnedEvent, SceneGraphGenerator, &SceneGraphGenerator::onEntitySpawnedEvent>(this);
        eventService.add<EntityDespawnedEvent, SceneGraphGenerator, &SceneGraphGenerator::onEntityDespawnedEvent>(this);
        eventService.add<EntityComponentAddedEvent<Graphics>, SceneGraphGenerator, &SceneGraphGenerator::onEntityComponentAddedEvent>(this);
        eventService.add<EntityComponentRemovedEvent<Graphics>, SceneGraphGenerator, &SceneGraphGenerator::onEntityComponentRemovedEvent>(this);
        eventService.add<EntityComponentAddedEvent<Camera>, SceneGraphGenerator, &SceneGraphGenerator::onEntityComponentAddedEvent>(this);
        eventService.add<EntityComponentRemovedEvent<Camera>, SceneGraphGenerator, &SceneGraphGenerator::onEntityComponentRemovedEvent>(this);
    }

    void SceneGraphGenerator::addCamera(Camera *c) {
        _root->addChild(c);
        c->addChild(&_sceneRoot);
    }

    void SceneGraphGenerator::removeCamera(Camera *c) {
        _root->removeChild(c);
        c->removeChild(&_sceneRoot);
    }

    void SceneGraphGenerator::onEntitySpawnedEvent(EntitySpawnedEvent& e) {
        Entity *entity = e.entity;
        if (entity->has<Graphics>())
            addGraphics(entity->get<Graphics>());
        if (entity->has<Camera>())
            addCamera(entity->get<Camera>());
    }

    void SceneGraphGenerator::onEntityDespawnedEvent(EntityDespawnedEvent& e) {
        Entity *entity = e.entity;
        if (entity->has<Graphics>())
            removeGraphics(entity->get<Graphics>());
        if (entity->has<Camera>())
            removeCamera(entity->get<Camera>());
    }

    void SceneGraphGenerator::onEntityComponentAddedEvent(EntityComponentAddedEvent<Graphics>& e) {
        addGraphics(e._component);
    }

    void SceneGraphGenerator::onEntityComponentRemovedEvent(EntityComponentRemovedEvent<Graphics>& e) {
        removeGraphics(e._component);
    }

    void SceneGraphGenerator::onEntityComponentAddedEvent(EntityComponentAddedEvent<Camera> &e) {
        addCamera(e._component);
    }

    void SceneGraphGenerator::onEntityComponentRemovedEvent(EntityComponentRemovedEvent<Camera> &e) {
        addCamera(e._component);
    }
}