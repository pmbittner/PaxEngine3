//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_KEYBOARD_H
#define PAXENGINE3_KEYBOARD_H

#include <SDL2/SDL_keycode.h>

namespace PAX {
    class InputSystem;

    class Keyboard {
    private:
        friend class InputSystem;
        bool keyDown[1 << 10];

    public:
        bool isKeyDown(SDL_Keycode key);
    };
}

#endif //PAXENGINE3_KEYBOARD_H
