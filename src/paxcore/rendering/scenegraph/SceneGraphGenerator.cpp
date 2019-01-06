//
// Created by Paul on 08.05.2017.
//

#include <paxcore/rendering/scenegraph/SceneGraphGenerator.h>
#include <paxcore/world/WorldLayer.h>

namespace PAX {
    SceneGraphGenerator::SceneGraphGenerator() {}
    SceneGraphGenerator::~SceneGraphGenerator() {}

    void SceneGraphGenerator::initialize(SceneGraph* root, EventService& eventService) {
        PAX_assertNotNull(root, "Root can't be null!");
        _root = root;

        eventService.add<EntitySpawnedEvent, SceneGraphGenerator, &SceneGraphGenerator::onEntitySpawnedEvent>(this);
        eventService.add<EntityDespawnedEvent, SceneGraphGenerator, &SceneGraphGenerator::onEntityDespawnedEvent>(this);
        eventService.add<PropertyAttachedEvent<Entity, Graphics>, SceneGraphGenerator, &SceneGraphGenerator::onEntityComponentAddedEvent>(this);
        eventService.add<PropertyDetachedEvent<Entity, Graphics>, SceneGraphGenerator, &SceneGraphGenerator::onEntityComponentRemovedEvent>(this);
        eventService.add<PropertyAttachedEvent<Entity, Camera>, SceneGraphGenerator, &SceneGraphGenerator::onEntityComponentAddedEvent>(this);
        eventService.add<PropertyDetachedEvent<Entity, Camera>, SceneGraphGenerator, &SceneGraphGenerator::onEntityComponentRemovedEvent>(this);
    }

    void SceneGraphGenerator::addCamera(Camera * c) {
        _root->addChild(c);
        c->addChild(&sceneRoot);

        _cameras.push_back(c);
    }

    void SceneGraphGenerator::removeCamera(Camera * c) {
        _root->removeChild(c);
        c->removeChild(&sceneRoot);

        Util::removeFromVector(_cameras, c);
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

    void SceneGraphGenerator::onEntityComponentAddedEvent(PropertyAttachedEvent<Entity, Graphics>& e) {
        addGraphics(e.property);
    }

    void SceneGraphGenerator::onEntityComponentRemovedEvent(PropertyDetachedEvent<Entity, Graphics>& e) {
        removeGraphics(e.property);
    }

    void SceneGraphGenerator::onEntityComponentAddedEvent(PropertyAttachedEvent<Entity, Camera> &e) {
        addCamera(e.property);
    }

    void SceneGraphGenerator::onEntityComponentRemovedEvent(PropertyDetachedEvent<Entity, Camera> &e) {
        addCamera(e.property);
    }

    const std::vector<Camera*>& SceneGraphGenerator::getCameras() const {
        return _cameras;
    }
}