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
        const std::vector<World*> & worlds = Engine::Instance().getGame()->getWorlds();

        for (World * w : worlds) {
            generationEntryPoint->addChild(w->getSceneGraph());
        }

        sceneGraphRoot->render(options);

        for (World * w : worlds) {
            generationEntryPoint->removeChild(w->getSceneGraph());
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