//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_MOUSE_H
#define PAXENGINE3_MOUSE_H

#include <paxutil/lib/GlmIncludes.h>

#include "../rendering/camera/Camera.h"
#include "MouseButtons.h"

namespace PAX {
    class InputSystem;

    class Mouse {
        friend class InputSystem;

        glm::ivec2 screenPos;

    public:
        const glm::ivec2 & getScreenPosition() const;
        bool isButtonDown(MouseButton button);

        static glm::ivec2 toViewportScreenCoordinates(const glm::ivec2 & screenPos, Camera& camera);
    };
}

#endif //PAXENGINE3_MOUSE_H
