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

        _gfxToSceneGraph[g] = node;
    }

    void ListSceneGraphGenerator::removeGraphics(Graphics *g) {
        SceneGraph *node = _gfxToSceneGraph[g];
        node->removeRenderable(g);

        _gfxToSceneGraph.erase(g);

        if (node->isEmpty()) {
            delete node; // node will unhook itself
        }
    }
}