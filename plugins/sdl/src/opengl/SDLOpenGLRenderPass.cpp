//
// Created by Paul on 17.06.2017.
//

#include <SDL2/SDL_video.h>
#include <opengl/SDLOpenGLRenderPass.h>
#include <SDLWindow.h>
#include <core/Engine.h>

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