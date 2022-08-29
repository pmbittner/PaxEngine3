//
// Created by paul on 15.06.17.
//

#ifndef PAXENGINE3_SDLOPENGLWINDOW_H
#define PAXENGINE3_SDLOPENGLWINDOW_H

#include "../SDLWindow.h"

namespace PAX {
    namespace SDL {
        namespace OpenGL {
            class SDLOpenGLWindow : public SDL::SDLWindow {
            private:
                SDL_GLContext _context;

            protected:
                Uint32 flags() override;

            public:
                SDLOpenGLWindow();
                ~SDLOpenGLWindow() override;

                bool create(const std::string& title, int width, int height) override;
                PAX_NODISCARD const SDL_GLContext & getContext() const;
            };
        }
    }
}

#endif //PAXENGINE3_SDLOPENGLWINDOW_H
