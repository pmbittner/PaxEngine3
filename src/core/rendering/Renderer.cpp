//
// Created by Paul on 29.04.2017.
//

#include "../../../include/core/rendering/Renderer.h"
#include "../../../include/test/SDLTestApplication2.h"
#include "../../../include/core/Engine.h"

namespace PAX {
    void Renderer::initialize() {

    }

    void Renderer::render() {
        /*
        SDL_TEST_APPLICATION2::render();
        /*/
        World *activeWorld = Engine::GetInstance()->getGame()->getActiveWorld();

        SceneGraph *scene = activeWorld->getMainLayer()->getSceneGraph();
        _generationEntryPoint->addChild(scene);
        _sceneGraphRoot->render();
        _generationEntryPoint->removeChild(scene);
        //*/
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