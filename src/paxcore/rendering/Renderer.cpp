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

            _generationEntryPoint->addChild(scene);
            _sceneGraphRoot->render(options);
            _generationEntryPoint->removeChild(scene);
        }
    }

    SceneGraph* Renderer::getSceneGraphGenerationEntryPoint() {
        return _generationEntryPoint;
    }

    void Renderer::setSceneGraphGenerationEntryPoint(SceneGraph *generationEntiryPoint) {
        assert(generationEntiryPoint);
        _generationEntryPoint = generationEntiryPoint;
    }

    SceneGraph* Renderer::getSceneGraphRoot() {
        return _sceneGraphRoot;
    }

    void Renderer::setSceneGraphRoot(SceneGraph *root) {
        assert(root);
        _sceneGraphRoot = root;
    }
}