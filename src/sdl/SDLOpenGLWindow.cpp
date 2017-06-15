//
// Created by paul on 15.06.17.
//


#include <GL/glew.h>
#include <SDL_opengl.h>

#include "../../include/sdl/SDLOpenGLWindow.h"
#include "../../include/lib/easylogging++.h"

namespace PAX {
    SDLOpenGLWindow::SDLOpenGLWindow() : SDLWindow() {

    }

    Uint32 SDLOpenGLWindow::flags() {
        return SDLWindow::flags() | SDL_WINDOW_OPENGL;
    }

    bool SDLOpenGLWindow::create(std::string title, int width, int height) {
        if (SDLWindow::create(title, width, height)) {
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

            SDL_GLContext SDL_GL_CreateContext(_window);
            glewExperimental = GL_TRUE;
            LOG(INFO) << "GLEW Init";
            glewInit();

            return true;
        }

        return false;
    }
}