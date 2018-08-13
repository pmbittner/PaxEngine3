//
// Created by Paul on 11.05.2017.
//

#ifndef PAXENGINE3_SDLINPUTSYSTEM_H
#define PAXENGINE3_SDLINPUTSYSTEM_H

#include <SDL2/SDL_events.h>

#include <core/io/InputSystem.h>
#include <core/io/Mouse.h>
#include <core/io/event/KeyPressedEvent.h>
#include <core/io/event/KeyReleasedEvent.h>
#include <core/io/event/MouseButtonPressedEvent.h>
#include <core/io/event/MouseButtonReleasedEvent.h>
#include <core/io/event/MouseMovedEvent.h>
#include <core/io/event/MouseWheelEvent.h>

#include "SDLKeyboard.h"

namespace PAX {
    namespace SDL {
        class SDLInputSystem : public InputSystem {
            SDL_Event _currentEvent;

            SDLKeyboard _keyboard;
            Mouse _mouse;

            // pre allocated event objects
            MouseButtonPressedEvent _mbPressed;
            MouseButtonReleasedEvent _mbReleased;
            MouseMovedEvent _mMoved;
            MouseWheelEvent _mWheel;

            KeyPressedEvent _keyPressed;
            KeyReleasedEvent _keyReleased;

        public:
            virtual void initialize() override;
            virtual void update() override;

            virtual SDLKeyboard *getKeyboard() override;
            virtual Mouse *getMouse() override;
        };
    }
}

#endif //PAXENGINE3_SDLINPUTSYSTEM_H
