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
                virtual Uint32 flags() override;

            public:
                SDLOpenGLWindow();
                virtual ~SDLOpenGLWindow();

                virtual bool create(const std::string& title, int width, int height) override;
            };
        }
    }
}

#endif //PAXENGINE3_SDLOPENGLWINDOW_H
