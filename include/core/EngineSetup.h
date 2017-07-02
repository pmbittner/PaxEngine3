//
// Created by Gordon on 16.05.2017.
//

#ifndef PAXENGINE3_ENGINESETUP_H
#define PAXENGINE3_ENGINESETUP_H

namespace PAX {
    class Engine;
    class Window;
    class InputSystem;
    class RenderFactory;

    class EngineSetup {
    public:
        virtual void initialize(Engine* engine) = 0;

        virtual Window* createWindow() = 0;
        virtual InputSystem* createInputSystem() = 0;
        virtual RenderFactory* createRenderFactory() = 0;
    };
}

#endif //PAXENGINE3_ENGINESETUP_H
