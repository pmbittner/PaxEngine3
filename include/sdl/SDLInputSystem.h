//
// Created by Paul on 11.05.2017.
//

#ifndef PAXENGINE3_SDLINPUTSYSTEM_H
#define PAXENGINE3_SDLINPUTSYSTEM_H

#include <SDL2/SDL_events.h>

#include "../core/io/InputSystem.h"
#include "../core/io/Keyboard.h"
#include "../core/io/Mouse.h"
#include "../core/io/MouseButtonPressedEvent.h"
#include "../core/io/MouseButtonReleasedEvent.h"

namespace PAX {
    namespace SDL {
        class SDLInputSystem : public InputSystem {
            SDL_Event _currentEvent;

            Keyboard _keyboard;
            Mouse _mouse;

            // pre allocated event objects
            MouseButtonPressedEvent _mbPressed;
            MouseButtonReleasedEvent _mbReleased;

            void updateMouseLocation();

        public:
            virtual void initialize() override;

            virtual void update() override;

            virtual Keyboard *getKeyboard() override;

            virtual Mouse *getMouse() override;
        };
    }
}

#endif //PAXENGINE3_SDLINPUTSYSTEM_H
