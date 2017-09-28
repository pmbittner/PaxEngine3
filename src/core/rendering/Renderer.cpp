//
// Created by Paul on 29.04.2017.
//

#include "../../../include/core/rendering/Renderer.h"
#include "../../../include/test/SDLTestApplication2.h"
#include "../../../include/core/Engine.h"
#include "../../../include/core/Game.h"

namespace PAX {
    void Renderer::initialize() {

    }

    void Renderer::render() {
        RenderOptions options;

        World *activeWorld = Engine::Instance()->getGame()->getActiveWorld();
        if (activeWorld) {
            SceneGraph *scene = activeWorld->getSceneGraph();

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