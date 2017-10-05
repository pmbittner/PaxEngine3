//
// Created by Paul on 04.10.2017.
//

#include <core/rendering/scenegraph/nodes/SortingNode.h>

namespace PAX {
    SortingNode::SortingNode() : SceneGraph() {}

    SortingNode::~SortingNode() {}

    void SortingNode::render(RenderOptions &renderOptions) {
        _sorter.insertionSort(_children);
        SceneGraph::render(renderOptions);
    }
}