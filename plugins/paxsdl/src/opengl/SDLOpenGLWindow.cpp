//
// Created by paul on 15.06.17.
//


#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <polypropylene/log/Errors.h>

#include "paxsdl/opengl/SDLOpenGLWindow.h"


namespace PAX {
    namespace SDL {
        namespace OpenGL {
            SDLOpenGLWindow::SDLOpenGLWindow() : SDLWindow(), _context() {

            }

            SDLOpenGLWindow::~SDLOpenGLWindow() {
                SDL_GL_DeleteContext(_context);
            }

            Uint32 SDLOpenGLWindow::flags() {
                return SDLWindow::flags() | SDL_WINDOW_OPENGL;
            }

            bool SDLOpenGLWindow::create(const std::string& title, int width, int height) {
                glewExperimental = GL_TRUE;

                SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);//3.2
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
                //SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

                if (SDLWindow::create(title, width, height)) {
                    _context = SDL_GL_CreateContext(_window);

                    GLenum err = glewInit();
                    if (err != GLEW_OK) {
                        PAX_THROW_RUNTIME_ERROR("Unable to initialize glew: " << reinterpret_cast<const char *>(glewGetErrorString(err)));
                    }

                    PAX_LOG(Log::Level::Info, "GLEW Init succeeded");

                    return true;
                }

                return false;
            }
        }
    }
}