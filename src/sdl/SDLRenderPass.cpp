//
// Created by Paul on 01.06.2017.
//

#include <SDL_render.h>
#include "../../include/sdl/SDLRenderPass.h"
#include "../../include/core/io/Window.h"
#include "../../include/sdl/SDLWindow.h"
#include "../../include/core/Engine.h"
#include "../../include/lib/easylogging++.h"

namespace PAX {
    namespace SDL {
        SDLRenderPass::SDLRenderPass() : SceneGraph() {

        }

        SDLRenderPass::~SDLRenderPass() {
            SDL_Quit();
        }

        void SDLRenderPass::initialize() {
            PAX::Window *window = PAX::Engine::GetInstance()->getWindow();
            SDL_Window *sdlWindow = static_cast<PAX::SDL::SDLWindow *>(window)->getSDL_Window();

            _renderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (_renderer == nullptr) {
                SDL_DestroyWindow(sdlWindow);
                LOG(ERROR) << "SDL_CreateRenderer Error: " << SDL_GetError();
                SDL_Quit();
                return;
            }
        }

        void SDLRenderPass::render(RenderOptions &renderOptions) {
            //First clear the _renderer
            SDL_RenderClear(_renderer);

            SceneGraph::render(renderOptions);

            //Update the screen
            SDL_RenderPresent(_renderer);
        }

        SDL_Renderer *SDLRenderPass::getSDLRenderer() {
            return _renderer;
        }
    }
}