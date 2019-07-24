//
// Created by Paul on 17.06.2017.
//

#include <SDL2/SDL_video.h>
#include <paxcore/Engine.h>

#include "paxsdl/opengl/SDLOpenGLContext.h"
#include "paxsdl/SDLWindow.h"

namespace PAX {
    namespace SDL {
        namespace OpenGL {
            SDLOpenGLContext::SDLOpenGLContext() = default;

            void SDLOpenGLContext::initialize() {}

            void SDLOpenGLContext::render(RenderOptions &renderOptions) {
                SceneGraph::render(renderOptions);

                // Unpack the shared pointer and static cast, as its validity was alread checked in SDLPureContext::initialize
                SDLWindow *window = static_cast<SDLWindow *>(Services::GetWindowService().getWindow().get());
                SDL_GL_SwapWindow(window->getSDL_Window());
            }
        }
    }
}