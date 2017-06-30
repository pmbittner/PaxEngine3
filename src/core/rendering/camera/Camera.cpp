//
// Created by Gordon on 16.05.2017.
//

#include "../../../../include/core/rendering/camera/Camera.h"
#include "../../../../include/core/entity/Entity.h"

namespace PAX {
    Camera::Camera(Viewport *viewport, Projection *projection) : _viewport(viewport), _projection(projection) {

    }

    void Camera::render(RenderOptions &renderOptions) {
        renderOptions.setCamera(this);

        _viewport->apply();
        SceneGraph::render(renderOptions);
    }

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

    Viewport* Camera::getViewport() {
        return _viewport;
    }

    Projection* Camera::getProjection() {
        return _projection;
    }
}