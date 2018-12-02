//
// Created by Paul on 01.06.2017.
//

#include <SDL2/SDL_render.h>
#include <easylogging++.h>
#include <SDLRenderPass.h>
#include <paxcore/io/Window.h>
#include <SDLWindow.h>
#include <paxcore/Engine.h>

namespace PAX {
    namespace SDL {
        SDLRenderPass::SDLRenderPass() : SceneGraph() {

        }

        SDLRenderPass::~SDLRenderPass() {

        }

        void SDLRenderPass::initialize() {
            const auto& windowAsSDLType = std::dynamic_pointer_cast<PAX::SDL::SDLWindow>(Services::GetWindowService().getWindow());
            if (!windowAsSDLType) {
                throw std::logic_error("[SDLRenderPass::initialize] Invalid Window found: Expected SDLWindow!");
            }

            SDL_Window* sdlWindow = windowAsSDLType->getSDL_Window();

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