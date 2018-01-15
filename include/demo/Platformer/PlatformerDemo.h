//
// Created by Paul on 06.01.2018.
//

#ifndef PAXENGINE3_JUMPNRUNDEMO_H
#define PAXENGINE3_JUMPNRUNDEMO_H

#include <core/rendering/camera/FullPixelScreenProjection.h>
#include <opengl/OpenGLViewport.h>
#include <core/io/resources/Path.h>
#include <core/rendering/resource/SpriteSheet.h>
#include <core/rendering/graphics/SpriteGraphics.h>
#include <core/rendering/graphics/SpriteSheetGraphics.h>

#include "demo/OpenGL/OpenGLDemo.h"
#include "PlayerControls.h"
#include "PlayerSpriteAnimation.h"

namespace PAX {
    namespace Platformer {
        class PlatformerDemo : public Demo::OpenGLDemo {
            World *_world = nullptr;
            Entity *_player = nullptr;

            SpriteSheetGraphics* playerGraphics;

            std::shared_ptr<Texture> centerBlockTexture;
            std::shared_ptr<Texture> leftBlockTexture;
            std::shared_ptr<Texture> rightBlockTexture;
            std::shared_ptr<Texture> spriteTest;

            std::shared_ptr<Shader> spriteShader, spriteSheetShader;


            void gatherResources() {
                LOG(INFO) << "PlatformerDemo: gatherResources";

                EntityComponentService& s = Services::GetEntityComponentService();

                spriteTest = Services::GetResources().loadOrGet<Texture>(
                        Services::GetPaths().RelativeResourcePath() + "img/Platformer/GreenBot16.png"
                );

                spriteShader = Services::GetResources().loadOrGet<Shader>(
                        Services::GetPaths().RelativeResourcePath() + "shader/sprite/sprite.vert",
                        Services::GetPaths().RelativeResourcePath() + "shader/sprite/sprite.frag"
                );

                playerGraphics = s.create<SpriteSheetGraphics>(spriteTest, 7, 4);
                spriteSheetShader = Services::GetResources().loadOrGet<Shader>(
                        playerGraphics->getShaderFlags(),
                        Services::GetPaths().RelativeResourcePath() + "shader/sprite/sprite.vert",
                        Services::GetPaths().RelativeResourcePath() + "shader/sprite/sprite.frag"
                );

                spriteShader->upload();
                spriteSheetShader->upload();

                playerGraphics->setShader(spriteSheetShader);
                playerGraphics->setSpriteScale({5, 5});
            }

            Entity* createPlayer() {
                LOG(INFO) << "PlatformerDemo: createPlayer";

                EntityComponentService& s = Services::GetEntityComponentService();

                Entity* player = new Entity();
                player->add(playerGraphics);
                
                player->add(s.create<PlayerControls>());
                player->add(s.create<PlayerSpriteAnimation>());

                /// Create Camera
                Entity* cameraChild = new Entity();
                cameraChild->add(s.create<Camera>(
                                new OpenGL::OpenGLViewport(),
                                new FullPixelScreenProjection()
                ));
                cameraChild->getTransform().z() = 1;
                cameraChild->setParent(player);

                return player;
            }

            Entity* createPlatform(int span) {
                LOG(INFO) << "PlatformerDemo: createPlatform of size " << span;

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
                    SpriteGraphics* g = s.create<SpriteGraphics>(tex);
                    g->setShader(spriteShader);
                    block->add(g);
                    block->getTransform().x() = x;
                    block->getTransform().scale2D() = {scale, scale};

                    block->setParent(platform);

                    tex = centerBlockTexture;
                }

                return platform;
            }

            void createEnvironment() {
                LOG(INFO) << "PlatformerDemo: createEnvironment";
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
                    SpriteGraphics* backgroundGraphics = s.create<SpriteGraphics>(
                            r.loadOrGet<Texture>(imgPath + "bg.png")
                    );
                    backgroundGraphics->setShader(spriteShader);
                    background->add(backgroundGraphics);

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
            PlatformerDemo() : OpenGLDemo() {
            }

            ~PlatformerDemo() {
                if (unregisterWorld(_world)) {
                    delete _world;
                } else {
                    LOG(ERROR) << "The world of JumpNRun could not be deleted!";
                }
            }

            virtual void initialize() override {
                OpenGLDemo::initialize();
                LOG(INFO) << "PlatformerDemo: initialize";

                gatherResources();

                //glActiveTexture(GL_TEXTURE0);

                _world = new World();
                _player = createPlayer();
                _world->getMainLayer()->spawn(_player);
                createEnvironment();

                std::cout << "Player Comp test" << std::endl;
                std::cout << "           Graphics: " << _player->get<Graphics>() << std::endl;
                std::cout << "     SpriteGraphics: " << _player->get<SpriteGraphics>() << std::endl;
                std::cout << "SpriteSheetGraphics: " << _player->get<SpriteSheetGraphics>() << std::endl;

                setActiveWorld(_world);
            }
        };
    }
}

#endif //PAXENGINE3_JUMPNRUNDEMO_H
