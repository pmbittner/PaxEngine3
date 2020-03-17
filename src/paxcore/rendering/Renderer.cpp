//
// Created by Paul on 29.04.2017.
//

#include <paxcore/rendering/Renderer.h>
#include <paxcore/Engine.h>
#include <paxcore/Game.h>

namespace PAX {
    void Renderer::initialize() {

    }

    void Renderer::render(RenderOptions & options) {
        World *activeWorld = Engine::Instance().getGame()->getActiveWorld();

        if (activeWorld) {
            WorldSceneGraph *scene = activeWorld->getSceneGraph();

            generationEntryPoint->addChild(scene);
            sceneGraphRoot->render(options);
            generationEntryPoint->removeChild(scene);
        }
    }

    SceneGraph* Renderer::getSceneGraphGenerationEntryPoint() {
        return generationEntryPoint;
    }

    void Renderer::setSceneGraphGenerationEntryPoint(SceneGraph *generationEntryPoint) {
        assert(generationEntryPoint);
        this->generationEntryPoint = generationEntryPoint;
    }

    SceneGraph* Renderer::getSceneGraphRoot() {
        return sceneGraphRoot;
    }

    void Renderer::setSceneGraphRoot(SceneGraph *root) {
        assert(root);
        sceneGraphRoot = root;
    }
}