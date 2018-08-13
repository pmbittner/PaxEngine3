//
// Created by bittner on 9/28/17.
//

#ifndef PAXENGINE3_SDLKEYBOARD_H
#define PAXENGINE3_SDLKEYBOARD_H

#include <SDL2/SDL_keycode.h>

#include <core/io/Keyboard.h>

namespace PAX {
    namespace SDL {
        class SDLKeyboard : public Keyboard {
            const Uint8 *_keyState = nullptr;

        public:
            virtual bool isKeyDown(Key key) override;
            bool isKeyDown(SDL_Scancode key);
            void setKeyStates(const Uint8 *keyState);
        };
    }
}

#endif //PAXENGINE3_SDLKEYBOARD_H
