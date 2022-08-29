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
            sortingNode.addChild(w->getSceneGraph());
        }

        sceneGraphRoot->render(options);

        for (World * w : worlds) {
            sortingNode.removeChild(w->getSceneGraph());
        }
    }

    SceneGraph* Renderer::getSceneGraphGenerationEntryPoint() const {
        return generationEntryPoint;
    }

    void Renderer::setSceneGraphGenerationEntryPoint(SceneGraph *generationEntryPoint) {
        if (generationEntryPoint == nullptr) {
            PAX_THROW_RUNTIME_ERROR("NullPointer: Cannot set nullptr as SceneGraphGenerationEntryPoint!");
        }
        if (!generationEntryPoint->isEmpty()) {
            PAX_THROW_RUNTIME_ERROR("NullPointer: Expected empty SceneGraphGenerationEntryPoint but the given scene graph has " << generationEntryPoint->size() << " children!");
        }
        this->generationEntryPoint = generationEntryPoint;
        this->generationEntryPoint->addChild(&sortingNode);
    }

    SceneGraph* Renderer::getSceneGraphRoot() const {
        return sceneGraphRoot;
    }

    void Renderer::setSceneGraphRoot(SceneGraph *root) {
        assert(root);
        sceneGraphRoot = root;
    }

    void WorldSorter::sort(std::vector<WorldSceneGraph *> &worlds) {
        std::sort(worlds.begin(), worlds.end(), [](WorldSceneGraph * a, WorldSceneGraph * b){
            return *a < *b;
        });
    }
}