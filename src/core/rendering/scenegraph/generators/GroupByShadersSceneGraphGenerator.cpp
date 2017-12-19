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

        if (shaderNode.isEmpty()) {
            // This is the first occurence of the shader.
            shaderNode.setShader(shader);
            _sceneRoot.addChild(&shaderNode);
        }

        shaderNode.addChild(graphics);
        graphics->OnShaderChanged.add<GroupByShadersSceneGraphGenerator, &GroupByShadersSceneGraphGenerator::onShaderChanged>(this);
    }

    void GroupByShadersSceneGraphGenerator::unregisterGraphicsFromShader(Graphics *graphics, Shader *shader) {
        ShadingNode &shaderNode = _shadersToNodes[shader];

        shaderNode.removeChild(graphics);

        // delete shader node if it no longer holds any graphics
        if (shaderNode.isEmpty()) {
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