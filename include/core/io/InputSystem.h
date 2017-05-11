//
// Created by Paul on 28.04.2017.
//

#ifndef PAXENGINE3_INPUTSYSTEM_H
#define PAXENGINE3_INPUTSYSTEM_H

#include "../interfaces/IEngineSystem.h"
#include "Keyboard.h"
#include "Mouse.h"

namespace PAX {
    class InputSystem : public IEngineSystem {
    public:
        virtual Keyboard* getKeyboard() = 0;
        virtual Mouse* getMouse() = 0;
    };
}

#endif //PAXENGINE3_INPUTSYSTEM_H
