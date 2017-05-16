//
// Created by Gordon on 16.05.2017.
//

#include "../../../include/core/rendering/Camera.h"
#include "../../../include/core/entity/Entity.h"

namespace PAX {
    const glm::mat4 & Camera::getViewTransform() {
        Entity *owner = getOwner();

        if (owner) {
            Transform &transform = owner->getTransform();
            _viewMatrix = glm::mat4(transform.toWorldMatrix());

            float x = _viewMatrix[3][0];
            float y = _viewMatrix[3][1];
            float z = _viewMatrix[3][2];
            _viewMatrix[3][0] = -(_viewMatrix[0][0] * x + _viewMatrix[1][0] * y + _viewMatrix[2][0] * z);
            _viewMatrix[3][1] = -(_viewMatrix[0][1] * x + _viewMatrix[1][1] * y + _viewMatrix[2][1] * z);
            _viewMatrix[3][2] = -(_viewMatrix[0][2] * x + _viewMatrix[1][2] * y + _viewMatrix[2][2] * z);
        } else
            _viewMatrix = glm::mat4(1.0f);

        return _viewMatrix;
    }
}