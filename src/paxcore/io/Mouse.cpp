//
// Created by Paul on 29.04.2017.
//

#include <easylogging++.h>
#include <paxcore/io/Mouse.h>

namespace PAX {
    const glm::ivec2 &  Mouse::getScreenPosition() const {
        return screenPos;
    }

    bool Mouse::isButtonDown(MouseButton button) {
        LOG(WARNING) << "Mouse::isButtonDown not implemented";
        return false;
    }

    glm::ivec2 Mouse::ScreenPosToViewportPos(const glm::ivec2 & screenPos, Camera &camera) {
        const auto& vp = camera.getViewport();
        return screenPos - glm::ivec2(vp->getX(), vp->getY());
    }

    glm::ivec2 Mouse::ViewportPosToWorldPos(const glm::ivec2 & viewportPos, PAX::Camera &camera) {
        const auto& vp = camera.getViewport();

        // TODO???: This may be packed into a single constant matrix, too.
        glm::vec2 projectedPos = (2.f * (glm::vec2(viewportPos.x, viewportPos.y) / glm::vec2(vp->getWidth(), vp->getHeight()))) - glm::vec2(1, 1);
        glm::vec4 pos = glm::inverse(camera.getViewTransform()) * (glm::inverse(camera.getProjection()->toMatrix()) * glm::vec4(projectedPos, 0, 1));

        return {pos.x, pos.y};
    }

    glm::ivec2 Mouse::ScreenPosToWorldPos(const glm::ivec2 & screenPos, PAX::Camera &camera) {
        return ViewportPosToWorldPos(ScreenPosToViewportPos(screenPos, camera), camera);
    }
}