//
// Created by bittner on 9/28/17.
//

#ifndef PAXENGINE3_RENDERTESTS_H
#define PAXENGINE3_RENDERTESTS_H

#include "../../core/Game.h"
#include "../../utility/io/CSVSettingsLoader.h"
#include "../../sdl/opengl/SDLOpenGLRenderPass.h"
#include "../../sdl/SDLRenderPass.h"
#include "../../core/Engine.h"

namespace PAX {
    namespace Demo {
        class RenderTests : public Game {
            Texture *cgTexture;

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
            RenderTests() : Game() {

            }

            ~RenderTests() {
                Services::GetResources().free(cgTexture);
            }

            virtual void initialize() override {
                EntityComponentService &componentAllocator = Services::GetEntityComponentService();

                // load graphic settings
                Util::CSVSettingsLoader graphicSettings(Services::GetPaths().RelativeResourcePath() + "config/graphics.ini", '=', true);
                int resX = graphicSettings.getInt("resolutionWidth");
                int resY = graphicSettings.getInt("resolutionHeight");

                Engine::Instance().getWindow()->create("PaxEngine3: RenderTests Demo", resX, resY);

                initRendering();
                LOG(INFO) << "RenderTests: Rendering initialized";

                World *world = new World();

                Entity *cameraEntity = new Entity();
                Camera *camera = componentAllocator.create<Camera>(
                        new OpenGL::OpenGLViewport(0, 0, resX, resY),
                        new FullPixelScreenProjection()
                );
                cameraEntity->add<Camera>(camera);
                cameraEntity->getTransform().setZ(1);
                LOG(INFO) << "RenderTests: Camera initialized";

                Entity *entity1 = new Entity();
                cgTexture = Services::GetResources().loadOrGet<Texture>("../../res/img/cg512.png");
                entity1->add<Graphics>(componentAllocator.create<OpenGL::OpenGLSprite>(cgTexture));
                //entity1->add<Behaviour>(new Dance2D());
                entity1->add<Behaviour>(componentAllocator.create<MoveToMouseBehaviour>());
                entity1->getTransform().setScale(200, 200);
                LOG(INFO) << "RenderTests: Entities initialized";

                world->getMainLayer()->spawn(cameraEntity);
                world->getMainLayer()->spawn(entity1);

                setActiveWorld(world);
                Game::initialize();

                LOG(INFO) << "RenderTests: Game initialized";
            }
        };
    }
}

#endif //PAXENGINE3_RENDERTESTS_H
