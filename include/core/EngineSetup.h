//
// Created by Gordon on 16.05.2017.
//

#ifndef PAXENGINE3_ENGINESETUP_H
#define PAXENGINE3_ENGINESETUP_H

#include "io/Window.h"
#include "io/InputSystem.h"

namespace PAX {
    class Engine;

    class EngineSetup {
    public:
        virtual void initialize(Engine* engine) = 0;

        virtual Window* createWindow() = 0;
        virtual InputSystem* createInputSystem() = 0;
    };
}

#endif //PAXENGINE3_ENGINESETUP_H
