//
// Created by Paul on 29.04.2017.
//

#include <paxcore/io/Mouse.h>

namespace PAX {
    const glm::ivec2 & Mouse::getScreenPosition() const {
        return screenPos;
    }

    bool Mouse::isButtonDown(MouseButton button) {
        PAX_NOT_IMPLEMENTED();
        return false;
    }

    glm::ivec2 Mouse::ScreenPosToViewportPos(const glm::ivec2 & screenPos, Camera &camera) {
        const auto& vp = camera.getViewport();
        glm::ivec2 vpPos = screenPos - glm::ivec2(vp->getX(), vp->getY());
        vpPos.y = vp->getHeight() - vpPos.y;
        return vpPos;
    }

    glm::ivec2 Mouse::ViewportPosToWorldPos(const glm::ivec2 & viewportPos, PAX::Camera &camera) {
        const auto& vp = camera.getViewport();

        // We have pixel screen corrdinates normalized to the viewport.
        // As we want to apply the matrix pipeline backwards, we need the device coordinates in range [-1, 1] for both dimension.
        glm::vec2 devicePos = (2.f * (glm::vec2(viewportPos) / glm::vec2(vp->getSize()))) - glm::vec2(1, 1);
        return glm::inverse(camera.getViewTransform()) * glm::inverse(camera.getProjection()->toMatrix()) * glm::vec4(devicePos, 0, 1);
    }

    glm::ivec2 Mouse::ScreenPosToWorldPos(const glm::ivec2 & screenPos, PAX::Camera &camera) {
        return ViewportPosToWorldPos(ScreenPosToViewportPos(screenPos, camera), camera);
    }
}