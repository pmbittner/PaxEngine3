//
// Created by Paul on 04.06.2017.
//

#include "../../../../include/core/rendering/Graphics.h"
#include "../../../../include/core/rendering/scenegraph/ListSceneGraphGenerator.h"

namespace PAX {
    void ListSceneGraphGenerator::addGraphics(Graphics *g) {
        SceneGraph *node = new SceneGraph();
        node->addRenderable(g);
        _sceneRoot.addChild(node);

        _gxToSceneGraph[g] = node;
    }

    void ListSceneGraphGenerator::removeGraphics(Graphics *g) {
        SceneGraph *node = _gxToSceneGraph[g];
        node->removeRenderable(g);

        auto iterator = _gxToSceneGraph.find(g);
        _gxToSceneGraph.erase(iterator);

        if (node->isEmpty()) {
            _gxToSceneGraph[g] = nullptr;
            delete node; // node will unhook itself
        }
    }
}