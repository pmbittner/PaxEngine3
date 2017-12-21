//
// Created by bittner on 9/28/17.
//

#ifndef PAXENGINE3_RENDERTESTS_H
#define PAXENGINE3_RENDERTESTS_H

#include "OpenGLDemo.h"

#include <core/rendering/resource/Texture.h>
#include <core/rendering/camera/FullPixelScreenProjection.h>
#include <opengl/OpenGLSprite.h>

namespace PAX {
    namespace Demo {
        class RenderTests : public OpenGLDemo {
        public:
            RenderTests() : OpenGLDemo() {

            }

            ~RenderTests() {

            }

            virtual void initialize() override {
                OpenGLDemo::initialize();

                EntityComponentService &componentAllocator = Services::GetEntityComponentService();
                Window* window = Engine::Instance().getWindow();

                World *world = new World();
                glm::ivec2 res = window->getResolution();

                Entity *cameraEntity = new Entity();
                Camera *camera = componentAllocator.create<Camera>(
                        new OpenGL::OpenGLViewport(0, 0, res.x, res.y),
                        new FullPixelScreenProjection()
                );
                cameraEntity->add<Camera>(camera);
                cameraEntity->getTransform().z() = 1;
                LOG(INFO) << "RenderTests: Camera initialized";

                Entity *entity1 = new Entity();
                std::shared_ptr<Texture> &cgTexture = Services::GetResources().loadOrGet<Texture>("../../res/img/cg512.png");
                entity1->add<Graphics>(componentAllocator.create<OpenGL::OpenGLSprite>(cgTexture));
                //entity1->add<Behaviour>(new Dance2D());
                entity1->add<Behaviour>(componentAllocator.create<MoveToMouseBehaviour>());
                entity1->getTransform().scale2D() = {200, 200};
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
