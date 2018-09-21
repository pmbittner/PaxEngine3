//
// Created by Paul on 28.04.2017.
//

#ifndef PAXENGINE3_INPUTSYSTEM_H
#define PAXENGINE3_INPUTSYSTEM_H

#include <paxutil/lib/GlmIncludes.h>

#include "../system/EngineSystem.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Window.h"

namespace PAX {
    class InputSystem : public EngineSystem {
    public:
        virtual Keyboard* getKeyboard() = 0;
        virtual Mouse* getMouse() = 0;

    protected:
        inline void setMouseScreenPosition(Mouse& mouse, int x, int y) {
            mouse.screenPos.x = x;
            mouse.screenPos.y = y;
        }

        inline void setWindowResolution(Window& window, const glm::ivec2 & res) {
            window._resolution = res;
        }
    };
}

#endif //PAXENGINE3_INPUTSYSTEM_H
