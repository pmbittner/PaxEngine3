//
// Created by Paul on 06.01.2018.
//

#ifndef PAXENGINE3_JUMPNRUNDEMO_H
#define PAXENGINE3_JUMPNRUNDEMO_H

#include <core/rendering/camera/FullPixelScreenProjection.h>
#include <opengl/OpenGLViewport.h>
#include <opengl/OpenGLSprite.h>
#include <core/io/resources/Path.h>
#include <core/rendering/resource/SpriteSheet.h>
#include "demo/OpenGL/OpenGLDemo.h"
#include "PlayerControls.h"

namespace PAX {
    namespace Demo {
        class JumpNRunDemo : public OpenGLDemo {
            World *_world = nullptr;
            Entity *_player = nullptr;

            std::shared_ptr<Texture> centerBlockTexture;
            std::shared_ptr<Texture> leftBlockTexture;
            std::shared_ptr<Texture> rightBlockTexture;

            std::shared_ptr<SpriteSheet> sprite;
            std::shared_ptr<Texture> spriteTest;

            Entity* createPlayer() {
                EntityComponentService& s = Services::GetEntityComponentService();

                Entity* player = new Entity();
                player->add<Behaviour>(
                        s.create<PlayerControls>()
                );

                sprite = Services::GetResources().loadOrGet<SpriteSheet>(
                        Services::GetPaths().RelativeResourcePath() + "img/Platformer/GreenBot16.png", 16, 16
                );
                spriteTest = std::shared_ptr<Texture>(sprite->getTextureAt(0));

                player->add<Graphics>(
                        s.create<OpenGL::OpenGLSprite>(
                                spriteTest
                        )
                );

                /// Create Camera
                Entity* cameraChild = new Entity();
                cameraChild->add(
                        s.create<Camera>(
                                new OpenGL::OpenGLViewport(),
                                new FullPixelScreenProjection()
                        )
                );
                cameraChild->getTransform().z() = 1;
                cameraChild->setParent(player);

                return player;
            }

            Entity* createPlatform(int span) {
                int scale = 5;
                EntityComponentService& s = Services::GetEntityComponentService();

                Entity* platform = new Entity();
                int w = centerBlockTexture->getWidth() * scale;
                int xMax = (span-1)*(w/2);

                std::shared_ptr<Texture> tex = leftBlockTexture;
                for (int x = -xMax; x <= xMax; x += w) {
                    if (x >= xMax)
                        tex = rightBlockTexture;

                    Entity *block = new Entity();
                    block->add<Graphics>(s.create<OpenGL::OpenGLSprite>(tex));
                    block->getTransform().x() = x;
                    block->getTransform().scale2D() = {scale, scale};

                    block->setParent(platform);

                    tex = centerBlockTexture;
                }

                return platform;
            }

            void createEnvironment() {
                EntityComponentService& s = Services::GetEntityComponentService();
                glm::vec2 resolution = Engine::Instance().getWindow()->getResolution();
                Resources &r = Services::GetResources();
                std::string imgPath = Services::GetPaths().RelativeResourcePath() + "img/Platformer/";

                centerBlockTexture = r.loadOrGet<Texture>(imgPath + "Block/Center.png");
                leftBlockTexture   = r.loadOrGet<Texture>(imgPath + "Block/Left.png");
                rightBlockTexture  = r.loadOrGet<Texture>(imgPath + "Block/Right.png");

                int w = centerBlockTexture->getWidth();
                int h = centerBlockTexture->getHeight();
                int y = resolution.y - 2*h;

                Entity *p1 = createPlatform(5);
                p1->getTransform().position2D() = {0, -200};
                _world->getMainLayer()->spawn(p1);

                Entity *p2 = createPlatform(2);
                p2->getTransform().position2D() = {300, 100};
                _world->getMainLayer()->spawn(p2);

                {
                    Entity *background = new Entity();
                    background->add<Graphics>(s.create<OpenGL::OpenGLSprite>(
                            r.loadOrGet<Texture>(imgPath + "bg.png")
                    ));

                    Entity *backgroundCam = new Entity();
                    backgroundCam->add(s.create<Camera>(
                            new OpenGL::OpenGLViewport(),
                            new FullPixelScreenProjection()
                    ));
                    backgroundCam->getTransform().z() = 1;

                    WorldLayer *bg = new WorldLayer("Background", -10);
                    bg->spawn(background);
                    bg->spawn(backgroundCam);
                    _world->addLayer(bg);
                }
            }

        public:
            JumpNRunDemo() : OpenGLDemo() {
            }

            ~JumpNRunDemo() {
                if (unregisterWorld(_world)) {
                    delete _world;
                } else {
                    LOG(ERROR) << "The world of JumpNRun could not be deleted!";
                }
            }

            virtual void initialize() override {
                OpenGLDemo::initialize();
                _world = new World();

                _player = createPlayer();
                createEnvironment();



                Entity *spriteMongo = new Entity();
                spriteMongo->add<Graphics>(
                        Services::GetEntityComponentService().create<OpenGL::OpenGLSprite>(
                                spriteTest
                        )
                );
                spriteMongo->getTransform().position2D() = {-200, 200};
                spriteMongo->getTransform().scale2D() = {5, 5};
                _world->getMainLayer()->spawn(spriteMongo);

                _world->getMainLayer()->spawn(_player);
                setActiveWorld(_world);
            }
        };
    }
}

#endif //PAXENGINE3_JUMPNRUNDEMO_H
