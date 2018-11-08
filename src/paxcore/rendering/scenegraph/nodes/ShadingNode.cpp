//
// Created by Paul on 05.10.2017.
//

#include <paxcore/rendering/scenegraph/nodes/ShadingNode.h>
#include <cassert>

PAX::ShadingNode::ShadingNode() : SceneGraph() {

}

PAX::ShadingNode::~ShadingNode() {

}

std::shared_ptr<PAX::Shader>& PAX::ShadingNode::getShader() {
    return _shader;
}

void PAX::ShadingNode::setShader(const std::shared_ptr<Shader>& shader) {
    ShadingNode::_shader = shader;
}

PAX::ShaderPriority PAX::ShadingNode::getPriority() const {
    return _priority;
}

void PAX::ShadingNode::setPriority(PAX::ShaderPriority priority) {
    ShadingNode::_priority = priority;
}

void PAX::ShadingNode::render(RenderOptions &renderOptions) {
    // Cache this in case, that shader will be reset during render. (should not happen)
    bool isShaded = _shader != nullptr;

    if (isShaded)
        renderOptions.getShaderOptions().pushShader(this, _shader, _priority);

    SceneGraph::render(renderOptions);

    if (isShaded)
        renderOptions.getShaderOptions().popShader(this);
}
