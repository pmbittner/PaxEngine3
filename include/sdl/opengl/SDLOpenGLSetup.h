//
// Created by Paul on 17.06.2017.
//

#ifndef PAXENGINE3_SDLOPENGLSETUP_H
#define PAXENGINE3_SDLOPENGLSETUP_H

#include "../SDLEngineSetup.h"
#include "SDLOpenGLWindow.h"

namespace PAX {
    class SDLOpenGLSetup : public SDLEngineSetup {
        virtual Window* createWindow() {
            return new SDLOpenGLWindow();
        }
    };
}

#endif //PAXENGINE3_SDLOPENGLSETUP_H
