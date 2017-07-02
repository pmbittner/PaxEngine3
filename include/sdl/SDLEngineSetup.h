//
// Created by Gordon on 16.05.2017.
//

#ifndef PAXENGINE3_SDLENGINESETUP_H
#define PAXENGINE3_SDLENGINESETUP_H

#include "../core/EngineSetup.h"

namespace PAX {
    namespace SDL {
        class SDLEngineSetup : public EngineSetup {
        public:
            virtual void initialize(Engine *engine) override;

            virtual Window *createWindow() override;
            virtual InputSystem *createInputSystem() override;
            virtual RenderFactory *createRenderFactory() override;
        };
    }
}

#endif //PAXENGINE3_SDLENGINESETUP_H
