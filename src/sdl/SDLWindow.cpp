//
// Created by Gordon on 16.05.2017.
//

#include "../../include/sdl/SDLWindow.h"
#include "../../include/lib/easylogging++.h"

namespace PAX {
    SDLWindow::SDLWindow() {

    }

    SDLWindow::~SDLWindow() {
        if (_window)
            SDL_DestroyWindow(_window);
    }

    bool SDLWindow::create(std::string title, int width, int height) {
        LOG(INFO) << "Create SDL Window (" << title << ", (" << width << "/" << height << "))";
        _window = SDL_CreateWindow(title.c_str(),
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  width,
                                  height,
                                  SDL_WINDOW_RESIZABLE);

        if (_window == NULL) {
            LOG(ERROR) << "Window could not be created: " << SDL_GetError();
        }
    }

    SDL_Window* SDLWindow::getSDL_Window() {
        return _window;
    }
}