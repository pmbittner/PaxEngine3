//
// Created by Gordon on 16.05.2017.
//

#include <core/rendering/camera/Camera.h>
#include <core/entity/Entity.h>
#include <utility/macros/MacroIncludes.h>

namespace PAX {
    Camera::Camera(std::shared_ptr<Viewport> viewport, std::shared_ptr<Projection> projection) : _viewport(viewport), _projection(projection) {
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
            _viewMatrix = transform.toWorldMatrix();
            // extracting upper left 3x3 part of the mat4
            glm::mat3 rotationMatrix(_viewMatrix);
            // invert the rotation (rotationMatrix is orthogonal => transpose = inverse)
            rotationMatrix = glm::transpose(rotationMatrix);
            // apply the rotation of the matrix to the displacement, as it isn't independent of the rotation,
            // meaning, that the look should rotate with its object
            glm::vec3 translation = rotationMatrix * glm::vec3(_viewMatrix[3]);
            _viewMatrix = glm::mat4(rotationMatrix);
            // invert translation
            _viewMatrix[3] = glm::vec4(-translation, 1);
        } else {
            _viewMatrix = glm::mat4(1.0f);
        }

        return _viewMatrix;
    }

    void Camera::onViewportWidthChanged(int oldWidth, int newWidth) {
        _projection->setResolutionWidth(newWidth);
    }

    void Camera::onViewportHeightChanged(int oldHeight, int newHeight) {
        _projection->setResolutionHeight(newHeight);
    }

    std::shared_ptr<Viewport> Camera::getViewport() {
        return _viewport;
    }

    std::shared_ptr<Projection> Camera::getProjection() {
        return _projection;
    }
}