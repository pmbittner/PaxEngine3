//
// Created by Paul on 07.01.2018.
//

#ifndef PAXENGINE3_WORLDSCENEGRAPH_H
#define PAXENGINE3_WORLDSCENEGRAPH_H

#include "WorldLayerSceneGraph.h"
#include <paxcore/rendering/scenegraph/nodes/SortingNode.h>

namespace PAX {
    class WorldLayerSceneGraphSort {
    public:
        void sort(std::vector<WorldLayerSceneGraph*> &graphics);
    };

    typedef SortingNode<WorldLayerSceneGraph, WorldLayerSceneGraphSort> WorldSceneGraph;
}
#endif //PAXENGINE3_WORLDSCENEGRAPH_H
