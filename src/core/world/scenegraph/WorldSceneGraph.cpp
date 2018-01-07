//
// Created by Paul on 07.01.2018.
//

#include <core/world/scenegraph/WorldSceneGraph.h>

void PAX::WorldLayerSceneGraphSort::sort(std::vector<WorldLayerSceneGraph*> &nodes) {
    int l = 0;
    int r = nodes.size() - 1;
    int i, j;
    WorldLayerSceneGraph *temp = nullptr;

    for (i = l + 1; i <= r; ++i) {
        temp = nodes[i];
        for (j = i; j > l && temp->getZ() < nodes[j-1]->getZ(); --j)
            nodes[j] = nodes[j-1];
        nodes[j] = temp;
    }
}