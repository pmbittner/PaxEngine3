//
// Created by Paul on 09.12.2017.
//

#ifndef PAXENGINE3_OPENGLDEMO_H
#define PAXENGINE3_OPENGLDEMO_H

#include <core/Game.h>
#include <core/Engine.h>
#include <opengl/rendernodes/OpenGLRenderPass.h>
#include <sdl/opengl/SDLOpenGLRenderPass.h>
#include <utility/io/CSVSettingsLoader.h>

namespace PAX {
    namespace Demo {
        class OpenGLDemo : public Game {
            void initRendering() {
                SDL::OpenGL::SDLOpenGLRenderPass *sdl = new SDL::OpenGL::SDLOpenGLRenderPass();
                OpenGL::OpenGLRenderPass *opengl = new OpenGL::OpenGLRenderPass();
                sdl->addChild(opengl);
                LOG(INFO) << "RenderTests: RenderPasses created";

                Renderer &renderer = Engine::Instance().getRenderer();

                renderer.setSceneGraphRoot(sdl);
                renderer.setSceneGraphGenerationEntryPoint(opengl);
                LOG(INFO) << "RenderTests: Nodes initialized";

                sdl->initialize();
                LOG(INFO) << "RenderTests: SDL initialized";
                opengl->initialize();
                LOG(INFO) << "RenderTests: OpenGL initialized";
            }

        public:
            OpenGLDemo() : Game() {

            }

            virtual void initialize() override {
                // load graphic settings
                Util::CSVSettingsLoader graphicSettings(Services::GetPaths().RelativeResourcePath() + "config/graphics.ini", '=', true);
                int resX = graphicSettings.getInt("resolutionWidth");
                int resY = graphicSettings.getInt("resolutionHeight");

                Engine::Instance().getWindow()->create("PaxEngine3: OpenGLDemo", resX, resY);

                initRendering();
                Game::initialize();
                LOG(INFO) << "RenderTests: Rendering initialized";
            }
        };
    }
}
#endif //PAXENGINE3_OPENGLDEMO_H
