//
// Created by Paul on 07.01.2018.
//

#include <paxcore/world/scenegraph/WorldLayerSceneGraph.h>

namespace PAX {
    WorldLayerSceneGraph::WorldLayerSceneGraph(float z) : _z(z) {

    }

    void WorldLayerSceneGraph::render(PAX::RenderOptions &renderOptions) {
        renderOptions.setWorldLayer(worldLayer);
        SceneGraph::render(renderOptions);
        renderOptions.setWorldLayer(nullptr);
    }

    float WorldLayerSceneGraph::getZ() {
        return _z;
    }

    void WorldLayerSceneGraph::setZ(float z) {
        _z = z;
    }
}