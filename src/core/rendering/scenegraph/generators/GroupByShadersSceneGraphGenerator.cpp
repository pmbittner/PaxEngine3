//
// Created by Paul on 05.10.2017.
//

#include <core/rendering/scenegraph/generators/GroupByShadersSceneGraphGenerator.h>
#include <core/rendering/scenegraph/nodes/SortingNode.h>

namespace PAX {
    GroupByShadersSceneGraphGenerator::GroupByShadersSceneGraphGenerator() {

    }

    GroupByShadersSceneGraphGenerator::~GroupByShadersSceneGraphGenerator() {

    }

    void GroupByShadersSceneGraphGenerator::registerGraphicsForShader(Graphics *graphics, Shader *shader) {
        ShadingNode &shaderNode = _shadersToNodes[shader];
        SortingNode *sortingNode = nullptr;

        if (shaderNode.isEmpty()) {
            // This is the first occurence of the shader. Hence, create new nodes below the scene root
            shaderNode.setShader(shader);
            sortingNode = new SortingNode();
            shaderNode.addChild(sortingNode);

            _sceneRoot.addChild(&shaderNode);
        } else {
            // This is not the first occurence of the shader. Hence, grab the
            // SortingNode below shaderNode, which is the only child of shaderNode.
            sortingNode = dynamic_cast<SortingNode*>(shaderNode.getChildren()[0]);
        }

        sortingNode->addChild(graphics);
        graphics->OnShaderChanged.add<GroupByShadersSceneGraphGenerator, &GroupByShadersSceneGraphGenerator::onShaderChanged>(this);
    }

    void GroupByShadersSceneGraphGenerator::unregisterGraphicsFromShader(Graphics *graphics, Shader *shader) {
        ShadingNode &shaderNode = _shadersToNodes[shader];
        // Grab the SortingNode below shaderNode, which is the only child of shaderNode.
        SortingNode* sortingNode = dynamic_cast<SortingNode*>(shaderNode.getChildren()[0]);

        sortingNode->removeChild(graphics);

        // delete shader node if it no longer holds any graphics
        if (sortingNode->isEmpty()) {
            // removes the entry for gShader from the map. This deletes the shader node, which deletes the sorting node
            _sceneRoot.removeChild(&shaderNode);
            _shadersToNodes.erase(shader);
        }

        graphics->OnShaderChanged.remove<GroupByShadersSceneGraphGenerator, &GroupByShadersSceneGraphGenerator::onShaderChanged>(this);
    }

    void GroupByShadersSceneGraphGenerator::addGraphics(Graphics *g) {
        registerGraphicsForShader(g, g->getShader());
    }

    void GroupByShadersSceneGraphGenerator::removeGraphics(Graphics *g) {
        unregisterGraphicsFromShader(g, g->getShader());
    }

    void GroupByShadersSceneGraphGenerator::onShaderChanged(GraphicsShaderChangedEvent &e) {
        unregisterGraphicsFromShader(e.graphics, e.oldShader);
        registerGraphicsForShader(e.graphics, e.newShader);
    }
}