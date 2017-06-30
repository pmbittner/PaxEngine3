//
// Created by Paul on 29.04.2017.
//

#include "../../../include/core/io/Keyboard.h"
#include "../../../include/lib/easylogging++.h"

namespace PAX {
    void Keyboard::setKeyStates(const Uint8* keyState) {
        _keyState = keyState;
    }

    bool Keyboard::isKeyDown(SDL_Scancode key) {
        return _keyState[key];
    }
}