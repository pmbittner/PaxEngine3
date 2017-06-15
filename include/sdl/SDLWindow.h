//
// Created by Gordon on 16.05.2017.
//

#ifndef PAXENGINE3_SDLWINDOW_H
#define PAXENGINE3_SDLWINDOW_H

#include <SDL_video.h>
#include <string>

#include "../core/io/Window.h"

namespace PAX {
    class SDLWindow : public Window {
    protected:
        SDL_Window *_window = nullptr;
        virtual Uint32 flags();

    public:
        SDLWindow();
        ~SDLWindow();

        virtual bool create(std::string title, int width, int height) override;

        SDL_Window* getSDL_Window();
    };
}

#endif //PAXENGINE3_SDLWINDOW_H
