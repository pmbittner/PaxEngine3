//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_MOUSE_H
#define PAXENGINE3_MOUSE_H

#include "MouseButtons.h"

namespace PAX {
    class InputSystem;

    class Mouse {
        int x, y;

        friend class InputSystem;
    public:
        int getX();
        int getY();
        bool isButtonDown(MouseButton button);
    };
}

#endif //PAXENGINE3_MOUSE_H
