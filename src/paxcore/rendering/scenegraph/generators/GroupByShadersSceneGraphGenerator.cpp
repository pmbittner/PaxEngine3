//
// Created by Paul on 05.10.2017.
//

#include <paxcore/rendering/scenegraph/generators/GroupByShadersSceneGraphGenerator.h>
#include <paxcore/rendering/scenegraph/nodes/SortingNode.h>

namespace PAX {
    GroupByShadersSceneGraphGenerator::GroupByShadersSceneGraphGenerator() = default;
    GroupByShadersSceneGraphGenerator::~GroupByShadersSceneGraphGenerator() = default;

    void GroupByShadersSceneGraphGenerator::registerGraphics(Graphics *graphics) {
        std::shared_ptr<Shader> &shader = graphics->getShader();
        ShadingNode &shaderNode = _shadersToNodes[shader.get()];

        if (shaderNode.isEmpty()) {
            // This is the first occurence of the shader.
            shaderNode.setShader(shader);
            sceneRoot.addChild(&shaderNode);
        }

        shaderNode.addChild(graphics);
        graphics->OnShaderChanged.add<GroupByShadersSceneGraphGenerator, &GroupByShadersSceneGraphGenerator::onShaderChanged>(this);
    }

    void GroupByShadersSceneGraphGenerator::unregisterGraphicsFromShader(Graphics *graphics, Shader* shader) {
        ShadingNode &shaderNode = _shadersToNodes[shader];

        shaderNode.removeChild(graphics);

        // delete shader node if it no longer holds any graphics
        if (shaderNode.isEmpty()) {
            sceneRoot.removeChild(&shaderNode);
            _shadersToNodes.erase(shader);
        }

        graphics->OnShaderChanged.remove<GroupByShadersSceneGraphGenerator, &GroupByShadersSceneGraphGenerator::onShaderChanged>(this);
    }

    void GroupByShadersSceneGraphGenerator::addGraphics(Graphics * g) {
        registerGraphics(g);
    }

    void GroupByShadersSceneGraphGenerator::removeGraphics(Graphics * g) {
        unregisterGraphicsFromShader(g, g->getShader().get());
    }

    void GroupByShadersSceneGraphGenerator::onShaderChanged(GraphicsShaderChangedEvent &e) {
        unregisterGraphicsFromShader(e.graphics, e.oldShader.get());
        registerGraphics(e.graphics);
    }
}