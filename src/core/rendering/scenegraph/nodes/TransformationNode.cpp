//
// Created by Paul on 06.01.2018.
//

#include <core/rendering/scenegraph/nodes/TransformationNode.h>

namespace PAX {
    TransformationNode::TransformationNode(const glm::mat4 &transformation) : _transformation(transformation) {

    }

    void TransformationNode::setTransformation(const glm::mat4 &transformation) {
        _transformation = transformation;
    }

    glm::mat4& TransformationNode::getTransformation() {
        return _transformation;
    }

    void TransformationNode::render(RenderOptions &options) {
        glm::mat4 oldTransform = options.getTransformation();

        options.setTransformation(oldTransform * _transformation);
        SceneGraph::render(options);
        options.setTransformation(oldTransform);
    }
}