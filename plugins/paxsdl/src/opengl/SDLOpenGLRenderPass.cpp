//
// Created by Paul on 17.06.2017.
//

#include <SDL2/SDL_video.h>
#include <opengl/SDLOpenGLRenderPass.h>
#include <SDLWindow.h>
#include <paxcore/Engine.h>

namespace PAX {
    namespace SDL {
        namespace OpenGL {
            SDLOpenGLRenderPass::SDLOpenGLRenderPass() {}

            void SDLOpenGLRenderPass::initialize() {}

            void SDLOpenGLRenderPass::render(RenderOptions &renderOptions) {
                SceneGraph::render(renderOptions);

                // Unpack the shared pointer and static cast, as its validity was alread checked in SDLRenderPass::initialize
                SDLWindow *window = static_cast<SDLWindow *>(Services::GetWindowService().getWindow().get());
                SDL_GL_SwapWindow(window->getSDL_Window());
            }
        }
    }
}