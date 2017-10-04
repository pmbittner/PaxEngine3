//
// Created by Paul on 17.06.2017.
//

#include <SDL_video.h>
#include "../../../include/sdl/opengl/SDLOpenGLRenderPass.h"
#include "../../../include/sdl/SDLWindow.h"
#include "../../../include/core/Engine.h"

namespace PAX {
    namespace SDL {
        namespace OpenGL {
            SDLOpenGLRenderPass::SDLOpenGLRenderPass() {}

            void SDLOpenGLRenderPass::initialize() {}

            void SDLOpenGLRenderPass::render(RenderOptions &renderOptions) {
                SceneGraph::render(renderOptions);
                //LOG(INFO) << "SDL_Bufferflip";
                SDLWindow *window = static_cast<SDLWindow *>(Engine::Instance().getWindow());
                SDL_GL_SwapWindow(window->getSDL_Window());
            }
        }
    }
}