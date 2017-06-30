//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_KEYBOARD_H
#define PAXENGINE3_KEYBOARD_H

#include <SDL2/SDL_keycode.h>

namespace PAX {
    class Keyboard {
        const Uint8* _keyState = 0;

    public:
        void setKeyStates(const Uint8* keyState);
        bool isKeyDown(SDL_Scancode key);
    };
}

#endif //PAXENGINE3_KEYBOARD_H
