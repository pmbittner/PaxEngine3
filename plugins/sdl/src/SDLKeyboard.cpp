//
// Created by bittner on 9/28/17.
//

#include <SDLKeyboard.h>

namespace PAX {
    namespace SDL {
        bool SDLKeyboard::isKeyDown(Key key) {
            return isKeyDown((SDL_Scancode)key);
        }

        void SDLKeyboard::setKeyStates(const Uint8* keyState) {
            _keyState = keyState;
        }

        bool SDLKeyboard::isKeyDown(SDL_Scancode key) {
            return _keyState[key];
        }
    }
}