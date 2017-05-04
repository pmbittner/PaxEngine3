//
// Created by Paul on 29.04.2017.
//

#include "../../../include/core/io/Keyboard.h"

namespace PAX {
    bool Keyboard::isKeyDown(SDL_Keycode key) {
        return keyDown[key];
    }
}