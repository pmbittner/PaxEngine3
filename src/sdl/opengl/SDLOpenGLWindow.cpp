//
// Created by paul on 15.06.17.
//


#include <GL/glew.h>
#include <SDL_opengl.h>

#include "../../../include/sdl/opengl/SDLOpenGLWindow.h"
#include "../../../include/lib/easylogging++.h"

namespace PAX {
    SDLOpenGLWindow::SDLOpenGLWindow() : SDLWindow() {

    }

    SDLOpenGLWindow::~SDLOpenGLWindow() {
        SDL_GL_DeleteContext(_context);
    }

    Uint32 SDLOpenGLWindow::flags() {
        return SDLWindow::flags() | SDL_WINDOW_OPENGL;
    }

    bool SDLOpenGLWindow::create(std::string title, int width, int height) {
        glewExperimental = GL_TRUE;

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);//3.2
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        //SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

        if (SDLWindow::create(title, width, height)) {
            _context = SDL_GL_CreateContext(_window);

            GLenum err = glewInit();
            if (err != GLEW_OK){
                LOG(INFO) << "GLEW Init failed";
                throw std::runtime_error(std::string("Unable to initialize glew: ") + reinterpret_cast<const char*>(glewGetErrorString(err)));
            }

            LOG(INFO) << "GLEW Init succeeded";

            return true;
        }

        return false;
    }
}