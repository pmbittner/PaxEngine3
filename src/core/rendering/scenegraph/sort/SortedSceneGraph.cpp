//
// Created by Paul on 04.10.2017.
//

#include <core/rendering/scenegraph/sort/SortedSceneGraph.h>

namespace PAX {
    SortedSceneGraph::SortedSceneGraph() : SceneGraph() {}

    SortedSceneGraph::~SortedSceneGraph() {}

    void SortedSceneGraph::render(RenderOptions &renderOptions) {
        _sorter.insertionSort(_children);
        SceneGraph::render(renderOptions);
    }
}