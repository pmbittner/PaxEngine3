//
// Created by paul on 07.01.19.
//

#ifndef PAXENGINE3_INPUTSYSTEMFACTORY_H
#define PAXENGINE3_INPUTSYSTEMFACTORY_H

#include "InputSystem.h"

namespace PAX {
    class InputSystemFactory {
    public:
        virtual std::shared_ptr<InputSystem> create() = 0;
    };
}

#endif //PAXENGINE3_INPUTSYSTEMFACTORY_H
