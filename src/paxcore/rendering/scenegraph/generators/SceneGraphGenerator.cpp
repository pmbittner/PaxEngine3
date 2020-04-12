//
// Created by Paul on 08.05.2017.
//

#include <paxcore/rendering/scenegraph/generators/SceneGraphGenerator.h>
#include <paxcore/rendering/renderpass/RenderPass.h>

namespace PAX {
    SceneGraphGenerator::SceneGraphGenerator() = default;
    SceneGraphGenerator::~SceneGraphGenerator() = default;

    void SceneGraphGenerator::initialize(SceneGraph* root, EventService& eventService) {
        PAX_ASSERT_NOT_NULL(root, "Root can't be null!");
        targetRoot = root;

        cameraChild.addChild(&sceneRoot);

        eventService.add<GameEntitySpawnedEvent, SceneGraphGenerator, &SceneGraphGenerator::onGameEntitySpawnedEvent>(this);
        eventService.add<GameEntityDespawnedEvent, SceneGraphGenerator, &SceneGraphGenerator::onGameEntityDespawnedEvent>(this);
        eventService.add<PropertyAttachedEvent<GameEntity, Graphics>, SceneGraphGenerator, &SceneGraphGenerator::onGameEntityComponentAddedEvent>(this);
        eventService.add<PropertyDetachedEvent<GameEntity, Graphics>, SceneGraphGenerator, &SceneGraphGenerator::onGameEntityComponentRemovedEvent>(this);
        eventService.add<PropertyAttachedEvent<GameEntity, Camera>, SceneGraphGenerator, &SceneGraphGenerator::onGameEntityComponentAddedEvent>(this);
        eventService.add<PropertyDetachedEvent<GameEntity, Camera>, SceneGraphGenerator, &SceneGraphGenerator::onGameEntityComponentRemovedEvent>(this);
    }

    void SceneGraphGenerator::terminate(PAX::EventService &eventService) {
        eventService.remove<GameEntitySpawnedEvent, SceneGraphGenerator, &SceneGraphGenerator::onGameEntitySpawnedEvent>(this);
        eventService.remove<GameEntityDespawnedEvent, SceneGraphGenerator, &SceneGraphGenerator::onGameEntityDespawnedEvent>(this);
        eventService.remove<PropertyAttachedEvent<GameEntity, Graphics>, SceneGraphGenerator, &SceneGraphGenerator::onGameEntityComponentAddedEvent>(this);
        eventService.remove<PropertyDetachedEvent<GameEntity, Graphics>, SceneGraphGenerator, &SceneGraphGenerator::onGameEntityComponentRemovedEvent>(this);
        eventService.remove<PropertyAttachedEvent<GameEntity, Camera>, SceneGraphGenerator, &SceneGraphGenerator::onGameEntityComponentAddedEvent>(this);
        eventService.remove<PropertyDetachedEvent<GameEntity, Camera>, SceneGraphGenerator, &SceneGraphGenerator::onGameEntityComponentRemovedEvent>(this);
    }

    void SceneGraphGenerator::addCamera(Camera * c) {
        targetRoot->addChild(c);
        c->addChild(&cameraChild);

        cameras.push_back(c);
    }

    void SceneGraphGenerator::removeCamera(Camera * c) {
        targetRoot->removeChild(c);
        c->removeChild(&cameraChild);

        Util::removeFromVector(cameras, c);
    }

    void SceneGraphGenerator::onGameEntitySpawnedEvent(GameEntitySpawnedEvent& e) {
        GameEntity *entity = e.entity;
        if (entity->has<Graphics>())
            addGraphics(entity->get<Graphics>());
        if (entity->has<Camera>())
            addCamera(entity->get<Camera>());
    }

    void SceneGraphGenerator::onGameEntityDespawnedEvent(GameEntityDespawnedEvent& e) {
        GameEntity *entity = e.entity;
        if (entity->has<Graphics>())
            removeGraphics(entity->get<Graphics>());
        if (entity->has<Camera>())
            removeCamera(entity->get<Camera>());
    }

    void SceneGraphGenerator::onGameEntityComponentAddedEvent(PropertyAttachedEvent<GameEntity, Graphics>& e) {
        addGraphics(e.property);
    }

    void SceneGraphGenerator::onGameEntityComponentRemovedEvent(PropertyDetachedEvent<GameEntity, Graphics>& e) {
        removeGraphics(e.property);
    }

    void SceneGraphGenerator::onGameEntityComponentAddedEvent(PropertyAttachedEvent<GameEntity, Camera> &e) {
        addCamera(e.property);
    }

    void SceneGraphGenerator::onGameEntityComponentRemovedEvent(PropertyDetachedEvent<GameEntity, Camera> &e) {
        addCamera(e.property);
    }

    const std::vector<Camera*>& SceneGraphGenerator::getCameras() const {
        return cameras;
    }

    void SceneGraphGenerator::addRenderPass(RenderPass *renderPass) {
        bool first = renderPasses.empty();
        renderPasses.push_back(renderPass);

        if (first) {
            cameraChild.dropChildren();
        }

        cameraChild.addChild(renderPass);
        renderPass->addChild(&sceneRoot);
    }

    const std::vector<RenderPass *> & SceneGraphGenerator::getRenderPasses() const {
        return renderPasses;
    }
}