//
// Created by Gordon on 16.05.2017.
//

#include <SDL2/SDL.h>
#include "../../include/sdl/SDLEngineSetup.h"
#include "../../include/sdl/SDLWindow.h"
#include "../../include/sdl/SDLInputSystem.h"

namespace PAX {
    void SDLEngineSetup::initialize(Engine* engine) {
        SDL_Init(SDL_INIT_EVERYTHING);
    }

    Window* SDLEngineSetup::createWindow() {
        return new SDLWindow();
    }

    InputSystem* SDLEngineSetup::createInputSystem() {
        return new SDLInputSystem();
    }
}