//
// Created by Paul on 01.06.2017.
//

#include <SDL2/SDL_render.h>

#include <paxcore/Engine.h>
#include <paxcore/io/Window.h>
#include "paxsdl/SDLPureContext.h"
#include "paxsdl/SDLWindow.h"

namespace PAX {
    namespace SDL {
        SDLPureContext::SDLPureContext() : SceneGraph() {

        }

        SDLPureContext::~SDLPureContext() = default;

        void SDLPureContext::initialize() {
            const auto& windowAsSDLType = std::dynamic_pointer_cast<PAX::SDL::SDLWindow>(Services::GetWindowService().getWindow());
            if (!windowAsSDLType) {
                PAX_THROW_RUNTIME_ERROR("Invalid Window found: Expected SDLWindow!");
            }

            SDL_Window* sdlWindow = windowAsSDLType->getSDL_Window();

            _renderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (_renderer == nullptr) {
                SDL_DestroyWindow(sdlWindow);
                PAX_LOG(Log::Level::Error, "SDL_CreateRenderer Error: " << SDL_GetError());
                SDL_Quit();
                return;
            }
        }

        void SDLPureContext::render(RenderOptions &renderOptions) {
            //First clear the _renderer
            SDL_RenderClear(_renderer);

            SceneGraph::render(renderOptions);

            //Update the screen
            SDL_RenderPresent(_renderer);
        }

        SDL_Renderer *SDLPureContext::getSDLRenderer() {
            return _renderer;
        }
    }
}