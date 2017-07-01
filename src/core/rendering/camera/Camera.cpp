//
// Created by Gordon on 16.05.2017.
//

#include "../../../../include/core/rendering/camera/Camera.h"
#include "../../../../include/core/entity/Entity.h"
#include "../../../../include/utility/MacroIncludes.h"

namespace PAX {
    Camera::Camera(Viewport *viewport, Projection *projection) : _viewport(viewport), _projection(projection) {
        PAX_assertNotNull(viewport, "Viewport can't be null!");
        PAX_assertNotNull(projection, "Projection can't be null!");

        viewport->WidthChanged.add<Camera, &Camera::onViewportWidthChanged>(this);
        viewport->HeightChanged.add<Camera, &Camera::onViewportHeightChanged>(this);

        projection->setResolutionWidth(viewport->getWidth());
        projection->setResolutionHeight(viewport->getHeight());
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

    void Camera::onViewportWidthChanged(int oldWidth, int newWidth) {
        _projection->setResolutionWidth(newWidth);
    }

    void Camera::onViewportHeightChanged(int oldHeight, int newHeight) {
        _projection->setResolutionHeight(newHeight);
    }

    Viewport* Camera::getViewport() {
        return _viewport;
    }

    Projection* Camera::getProjection() {
        return _projection;
    }
}