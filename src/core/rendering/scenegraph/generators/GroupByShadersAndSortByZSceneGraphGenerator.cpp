//
// Created by Paul on 06.01.2018.
//

#include <core/rendering/scenegraph/generators/GroupByShadersAndSortByZSceneGraphGenerator.h>

namespace PAX {
    void GroupByShadersAndSortByZSceneGraphGenerator::attach(ShadingNode &shadingNode, Graphics *g) {
        SortingNode *sorter = nullptr;

        if (shadingNode.isEmpty()) {
            sorter = new SortingNode();
            shadingNode.addChild(sorter);
        } else {
            sorter = static_cast<SortingNode*>(shadingNode.getChildren()[0]);
        }

        sorter->addChild(g);
    }

    void GroupByShadersAndSortByZSceneGraphGenerator::detach(ShadingNode &shadingNode, Graphics *g) {
        SortingNode *sorter = static_cast<SortingNode*>(shadingNode.getChildren()[0]);
        sorter->removeChild(g);

        if (sorter->isEmpty()) {
            shadingNode.removeChild(sorter);
            delete sorter;
        }
    }
}