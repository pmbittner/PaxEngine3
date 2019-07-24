//
// Created by Paul on 01.06.2017.
//

#ifndef PAXENGINE3_SDLPURECONTEXT_H
#define PAXENGINE3_SDLPURECONTEXT_H

#include <SDL2/SDL.h>
#include <paxcore/rendering/scenegraph/SceneGraph.h>

namespace PAX {
    namespace SDL {
        /**
         * Context for pure SDL rendering without OpenGL.
         */
        class SDLPureContext : public SceneGraph {
            SDL_Renderer *_renderer = nullptr;

        public:
            SDLPureContext();
            ~SDLPureContext() override;

            void initialize();

            void render(RenderOptions &renderOptions) override;

            SDL_Renderer *getSDLRenderer();
        };
    }
}

#endif //PAXENGINE3_SDLPURECONTEXT_H
