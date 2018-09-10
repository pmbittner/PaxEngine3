//
// Created by Paul on 07.01.2018.
//

#include <paxcore/world/scenegraph/WorldLayerSceneGraph.h>

namespace PAX {
    WorldLayerSceneGraph::WorldLayerSceneGraph(float z) : _z(z) {

    }

    float WorldLayerSceneGraph::getZ() {
        return _z;
    }

    void WorldLayerSceneGraph::setZ(float z) {
        _z = z;
    }
}