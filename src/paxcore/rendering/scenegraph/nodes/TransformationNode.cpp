//
// Created by Paul on 06.01.2018.
//

#include <paxcore/rendering/scenegraph/nodes/TransformationNode.h>

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
        const glm::mat4 parentTransform = options.getTransformationMatrix();

        options.setTransformationMatrix(parentTransform * _transformation);
        SceneGraph::render(options);
        options.setTransformationMatrix(parentTransform);
    }
}