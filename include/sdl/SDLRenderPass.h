//
// Created by Paul on 01.06.2017.
//

#ifndef PAXENGINE3_SDLRENDERPASS_H
#define PAXENGINE3_SDLRENDERPASS_H

#include <SDL2/SDL.h>
#include "../core/rendering/scenegraph/SceneGraph.h"

namespace PAX {
    namespace SDL {
        class SDLRenderPass : public SceneGraph {
            SDL_Renderer *_renderer = nullptr;

        public:
            SDLRenderPass();

            virtual ~SDLRenderPass();

            void initialize();

            virtual void render(RenderOptions &renderOptions) override;

            SDL_Renderer *getSDLRenderer();
        };
    }
}

#endif //PAXENGINE3_SDLRENDERPASS_H
