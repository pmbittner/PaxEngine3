//
// Created by Paul on 04.05.2017.
//

#include "../../../../include/core/rendering/scenegraph/SceneGraph.h"
#include "../../../../include/core/rendering/scenegraph/sort/RenderableSort.h"

namespace PAX {
    SceneGraph::SceneGraph() {
        int* intpointerlol = new int;
        delete intpointerlol;
    }

    void SceneGraph::render() {
        _sorter.insertionSort(&_children);

        for (Renderable *child : _children)
            child->render();
    }

    float SceneGraph::getZ() {
        if (!_children.empty())
            return _children[0]->getZ();
        return 0;
    }
}