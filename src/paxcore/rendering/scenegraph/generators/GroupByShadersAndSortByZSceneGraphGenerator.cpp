//
// Created by Paul on 06.01.2018.
//

#include <paxcore/rendering/scenegraph/generators/GroupByShadersAndSortByZSceneGraphGenerator.h>

namespace PAX {
    void GroupByShadersAndSortByZSceneGraphGenerator::attach(ShadingNode &shadingNode, Graphics *g) {
        GraphicsSortingNode2D *sorter = nullptr;

        if (shadingNode.isEmpty()) {
            sorter = new GraphicsSortingNode2D();
            shadingNode.addChild(sorter);
        } else {
            sorter = static_cast<GraphicsSortingNode2D*>(shadingNode.getChildren()[0]);
        }

        sorter->addChild(g);
    }

    void GroupByShadersAndSortByZSceneGraphGenerator::detach(ShadingNode &shadingNode, Graphics *g) {
        GraphicsSortingNode2D *sorter = static_cast<GraphicsSortingNode2D*>(shadingNode.getChildren()[0]);
        sorter->removeChild(g);

        if (sorter->isEmpty()) {
            shadingNode.removeChild(sorter);
            delete sorter;
        }
    }
}