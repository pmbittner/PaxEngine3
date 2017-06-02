//
// Created by Paul on 02.06.2017.
//

#include "../../../../include/core/rendering/scenegraph/SceneGraphGeneratable.h"

namespace PAX {
    SceneGraph * SceneGraphGeneratable::getSceneGraphNode() {
        return _mySceneGraphNode;
    }

    void SceneGraphGeneratable::setSceneGraphNode(SceneGraph *sceneGraph) {
        _mySceneGraphNode = sceneGraph;
    }
}