//
// Created by Gordon on 16.05.2017.
//

#include <SDL2/SDL.h>
#include <core/service/Paths.h>
#include <sdl/utility/Path.h>
#include <core/service/Services.h>
//#include <SDL_ttf.h>
#include "../../include/sdl/SDLEngineSetup.h"
#include "../../include/sdl/SDLWindow.h"
#include "../../include/sdl/SDLInputSystem.h"
#include "../../include/sdl/SDLRenderFactory.h"

namespace PAX {
    namespace SDL {
        void SDLEngineSetup::initialize(Engine *engine) {
            SDL_Init(SDL_INIT_EVERYTHING);//TTF_Init();

            Services::GetPaths().setExecutionDirectory(getBasePath());
        }

        Window *SDLEngineSetup::createWindow() {
            return new SDLWindow();
        }

        InputSystem *SDLEngineSetup::createInputSystem() {
            return new SDLInputSystem();
        }

        RenderFactory * SDLEngineSetup::createRenderFactory() {
            return new SDLRenderFactory();
        }

        void SDLEngineSetup::registerServices() {
            EngineSetup::registerServices();
        }
    }
}