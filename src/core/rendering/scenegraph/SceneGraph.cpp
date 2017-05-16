//
// Created by Paul on 04.05.2017.
//

#include "../../../../include/core/rendering/scenegraph/SceneGraph.h"
#include "../../../../include/core/rendering/scenegraph/sort/RenderableSort.h"

namespace PAX {
    SceneGraph::SceneGraph() {

    }

    void SceneGraph::render() {
        _sorter.insertionSort(_children);

        for (Renderable *child : _children)
            child->render();
    }

    float SceneGraph::getZ() {
        return _z;
    }

    void SceneGraph::setZ(float z) {
        _z = z;
    }
}