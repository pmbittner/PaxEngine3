//
// Created by Gordon on 16.05.2017.
//

#ifndef PAXENGINE3_SDLWINDOW_H
#define PAXENGINE3_SDLWINDOW_H

#include <SDL2/SDL_video.h>
#include <string>
#include <paxutil/lib/GlmIncludes.h>

#include <paxcore/io/Window.h>

namespace PAX {
    namespace SDL {
        class SDLInputSystem;

        class SDLWindow : public Window {
            friend class SDLInputSystem;

        protected:
            SDL_Window *_window = nullptr;

            virtual Uint32 flags();

        public:
            SDLWindow();

            virtual ~SDLWindow();

            virtual bool create(const std::string& title, int width, int height);
            virtual void setFullscreen(bool fullscreen) override;

            SDL_Window *getSDL_Window();
        };
    }
}

#endif //PAXENGINE3_SDLWINDOW_H
