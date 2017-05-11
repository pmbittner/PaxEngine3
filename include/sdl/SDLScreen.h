//
// Created by Paul on 11.05.2017.
//

#ifndef PAXENGINE3_SDLSCREEN_H
#define PAXENGINE3_SDLSCREEN_H

#include "../core/io/Screen.h"

namespace PAX {
    class SDLScreen : public Screen {
    public:
        SDLScreen(int w = 800, int h = 600);
        ~SDLScreen();

        virtual void initialize() override;
    };
}

#endif //PAXENGINE3_SDLSCREEN_H
