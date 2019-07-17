//
// Created by Paul on 11.05.2017.
//

#ifndef PAXENGINE3_SDLINPUTSYSTEM_H
#define PAXENGINE3_SDLINPUTSYSTEM_H

#include <SDL2/SDL_events.h>

#include <paxcore/io/InputSystem.h>
#include <paxcore/io/Mouse.h>
#include <paxcore/io/event/KeyPressedEvent.h>
#include <paxcore/io/event/KeyReleasedEvent.h>
#include <paxcore/io/event/MouseButtonPressedEvent.h>
#include <paxcore/io/event/MouseButtonReleasedEvent.h>
#include <paxcore/io/event/MouseMovedEvent.h>
#include <paxcore/io/event/MouseWheelEvent.h>

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
            void initialize() override;
            void terminate() override;
            void update(UpdateOptions & options) override;

            virtual SDLKeyboard *getKeyboard() override;
            virtual Mouse *getMouse() override;
        };
    }
}

#endif //PAXENGINE3_SDLINPUTSYSTEM_H
