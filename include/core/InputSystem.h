//
// Created by Paul on 28.04.2017.
//

#ifndef PAXENGINE3_INPUTSYSTEM_H
#define PAXENGINE3_INPUTSYSTEM_H

#include <SDL2/SDL_events.h>

#include "interfaces/IEngineSystem.h"
#include "io/Keyboard.h"
#include "io/Mouse.h"

namespace PAX {
    class InputSystem : private IEngineSystem {
    private:
        SDL_Event _currentEvent;

        Keyboard _keyboard;
        Mouse _mouse;

        void updateMouseLocation();

    public:
        virtual void initialize() override;
        virtual void update() override;

        Keyboard* getKeyboard();
        Mouse* getMouse();
    };
}

#endif //PAXENGINE3_INPUTSYSTEM_H
