//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_KEYBOARD_H
#define PAXENGINE3_KEYBOARD_H

#include <SDL2/SDL_keycode.h>

namespace PAX {
    class Keyboard {
    public:
        bool keyDown[1 << 10];
        bool isKeyDown(SDL_Keycode key);
    };
}

#endif //PAXENGINE3_KEYBOARD_H
