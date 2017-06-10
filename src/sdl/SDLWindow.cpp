//
// Created by Gordon on 16.05.2017.
//

#include <GL/glew.h>
#include <SDL_opengl.h>

#include "../../include/sdl/SDLWindow.h"
#include "../../include/lib/easylogging++.h"

namespace PAX {
    SDLWindow::SDLWindow(bool isOpenGL) : _isOpenGL(isOpenGL) {

    }

    SDLWindow::~SDLWindow() {
        if (_window)
            SDL_DestroyWindow(_window);
    }

    bool SDLWindow::create(std::string title, int width, int height) {
        LOG(INFO) << "Create SDL Window (" << title << ", (" << width << "/" << height << "))";

        Uint32 flags = SDL_WINDOW_RESIZABLE;

        if (_isOpenGL) {
            flags |= SDL_WINDOW_OPENGL;

            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        }

        _window = SDL_CreateWindow(title.c_str(),
                                   SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED,
                                   width,
                                   height,
                                   flags);

        if (_window == NULL) {
            LOG(ERROR) << "Window could not be created: " << SDL_GetError();
        }

        if (_isOpenGL) {
            SDL_GLContext SDL_GL_CreateContext(_window);
            glewExperimental = GL_TRUE;
            LOG(INFO) << "GLEW Init";
            //glewInit();
        }
    }

    SDL_Window* SDLWindow::getSDL_Window() {
        return _window;
    }
}