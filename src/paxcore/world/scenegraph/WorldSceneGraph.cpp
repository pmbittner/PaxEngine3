//
// Created by Paul on 07.01.2018.
//

//#include <paxcore/world/scenegraph/WorldSceneGraph.h>

#include <paxcore/world/scenegraph/WorldSceneGraph.h>

namespace PAX {
    void WorldSceneGraph::render(PAX::RenderOptions &renderOptions) {
        renderOptions.setWorld(world);
        SceneGraph::render(renderOptions);
        renderOptions.setWorld(nullptr);
    }

    World* WorldSceneGraph::getWorld() {
        return world;
    }
}