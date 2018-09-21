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

    glm::ivec2 Mouse::toViewportScreenCoordinates(const glm::ivec2 & screenPos, Camera &camera) {
        const auto& vp = camera.getViewport();
        return screenPos - glm::ivec2(vp->getX(), vp->getY());
    }
}