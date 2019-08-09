//
// Created by Bittner on 16.05.2017.
//

#include <paxsdl/SDLWindow.h>
#include <paxutil/log/Log.h>

namespace PAX {
    namespace SDL {
        SDLWindow::SDLWindow() = default;

        SDLWindow::~SDLWindow() = default;

        void SDLWindow::dispose() {
            setFullscreen(false);

            if (_window)
                SDL_DestroyWindow(_window);
        }

        Uint32 SDLWindow::flags() {
            return SDL_WINDOW_RESIZABLE;
        }

        bool SDLWindow::create(const std::string& title, int width, int height) {
            _resolution.x = width;
            _resolution.y = height;

            _window = SDL_CreateWindow(title.c_str(),
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       width,
                                       height,
                                       flags());

            if (_window == NULL) {
                PAX_LOG(Log::Level::Error, "[SDLWindow::create] Window could not be created: " << SDL_GetError());
                return false;
            }

            return true;
        }

        void SDLWindow::setFullscreen(bool fullscreen) {
            if (fullscreen && !isFullscreen()) {
                SDL_SetWindowFullscreen(_window, flags() | SDL_WINDOW_FULLSCREEN);
            } else if (!fullscreen && isFullscreen()) {
                SDL_SetWindowFullscreen(_window, flags());
            }

            Window::setFullscreen(fullscreen);
        }

        SDL_Window *SDLWindow::getSDL_Window() {
            return _window;
        }
    }
}