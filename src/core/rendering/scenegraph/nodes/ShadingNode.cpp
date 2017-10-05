//
// Created by Paul on 05.10.2017.
//

#include <core/rendering/scenegraph/nodes/ShadingNode.h>
#include <cassert>

PAX::ShadingNode::ShadingNode() : SceneGraph() {

}

PAX::ShadingNode::~ShadingNode() {
    // do not delete shader, since we do not own it
}

PAX::Shader *PAX::ShadingNode::getShader() const {
    return shader;
}

void PAX::ShadingNode::setShader(PAX::Shader *shader) {
    ShadingNode::shader = shader;
}

PAX::ShaderPriority PAX::ShadingNode::getPriority() const {
    return priority;
}

void PAX::ShadingNode::setPriority(PAX::ShaderPriority priority) {
    ShadingNode::priority = priority;
}

void PAX::ShadingNode::render(RenderOptions &renderOptions) {
    // Cache this in case, that shader will be reset during render. (should not happen)
    bool isShaded = shader != nullptr;

    if (isShaded)
        renderOptions.getShaderOptions().useShader(this, shader, ShaderPriority::MUTABLE);

    SceneGraph::render(renderOptions);

    if (isShaded)
        renderOptions.getShaderOptions().unuseShader(this);
}
