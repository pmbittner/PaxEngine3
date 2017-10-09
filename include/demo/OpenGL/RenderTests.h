//
// Created by bittner on 9/28/17.
//

#ifndef PAXENGINE3_RENDERTESTS_H
#define PAXENGINE3_RENDERTESTS_H

#include "../../core/Game.h"
#include "../../utility/io/CSVSettingsLoader.h"
#include "../../sdl/utitlity/Path.h"
#include "../../sdl/opengl/SDLOpenGLRenderPass.h"
#include "../../sdl/SDLRenderPass.h"
#include "../../core/Engine.h"

namespace PAX {
    namespace Demo {
        class RenderTests : public Game {

            void initRendering() {
                SDL::SDLRenderPass* sdl = new SDL::SDLRenderPass();
                SDL::OpenGL::SDLOpenGLRenderPass* opengl = new SDL::OpenGL::SDLOpenGLRenderPass();
                sdl->addChild(opengl);

                Renderer &renderer = Engine::Instance().getRenderer();

                renderer.setSceneGraphRoot(sdl);
                renderer.setSceneGraphGenerationEntryPoint(opengl);

                sdl->initialize();
                opengl->initialize();
            }

        public:
            RenderTests() : Game() {

            }

            virtual void initialize() override {
                // load graphic settings
                Util::CSVSettingsLoader graphicSettings(getResourcePath() + "config/graphics.ini", '=', true);
                int resX = graphicSettings.getInt("resolutionWidth");
                int resY = graphicSettings.getInt("resolutionHeight");

                Engine::Instance().getWindow()->create("PaxEngine3: RenderTests Demo", resX, resY);

                initRendering();

                World *world = new World();


                setActiveWorld(world);
                Game::initialize();
            }
        };
    }
}

#endif //PAXENGINE3_RENDERTESTS_H
