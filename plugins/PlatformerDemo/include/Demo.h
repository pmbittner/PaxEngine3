//
// Created by Paul on 06.01.2018.
//

#ifndef PAXENGINE3_JUMPNRUNDEMO_H
#define PAXENGINE3_JUMPNRUNDEMO_H

#include <paxcore/Game.h>
#include <paxcore/Engine.h>

#include <paxcore/entity/component/Size.h>
#include <paxutil/io/Path.h>
#include <paxcore/rendering/camera/FullPixelScreenProjection.h>
#include <paxcore/rendering/data/SpriteSheet.h>
#include <paxcore/rendering/graphics/SpriteGraphics.h>
#include <paxcore/rendering/graphics/SpriteSheetGraphics.h>
#include <PlatformerDemo/include/behaviour/DragNDrop.h>

#include "behaviour/PlayerControls.h"
#include "behaviour/PlayerSpriteAnimation.h"
#include "behaviour/FollowEntityBehaviour.h"

namespace PAX {
    namespace PlatformerDemo {
        class Demo : public Game {
            World *_world = nullptr;
            WorldLayer *_mainLayer = nullptr;
            Entity *_player = nullptr;
            Entity* _camera = nullptr;

            SpriteSheetGraphics* playerGraphics = nullptr;

            std::shared_ptr<Texture> centerBlockTexture;
            std::shared_ptr<Texture> leftBlockTexture;
            std::shared_ptr<Texture> rightBlockTexture;

            std::shared_ptr<Shader> spriteShader, spriteSheetShader;


            void gatherResources() {
                LOG(INFO) << "Demo: gatherResources";

                EntityComponentService& s = Services::GetEntityComponentService();

                std::shared_ptr<Texture> spriteTest = Services::GetResources().loadOrGet<Texture>(
                        Services::GetPaths().getResourcePath() + "/img/Platformer/GreenBot16.png"
                );

                spriteShader = Services::GetResources().loadOrGet<Shader>(
                        Services::GetPaths().getResourcePath() + "/shader/sprite/sprite.vert",
                        Services::GetPaths().getResourcePath() + "/shader/sprite/sprite.frag"
                );

                playerGraphics = s.create<SpriteSheetGraphics>(spriteTest, 7, 4);
                spriteSheetShader = Services::GetResources().loadOrGet<Shader>(
                        playerGraphics->getShaderFlags(),
                        Services::GetPaths().getResourcePath() + "/shader/sprite/sprite.vert",
                        Services::GetPaths().getResourcePath() + "/shader/sprite/sprite.frag"
                );

                spriteShader->upload();
                spriteSheetShader->upload();

                playerGraphics->setShader(spriteSheetShader);
            }

            Entity* createPlayer() {
                EntityComponentService& s = Services::GetEntityComponentService();

                Entity* player = new Entity();
                player->add(playerGraphics);
                player->add(s.create<VelocityBehaviour>());
                player->add(s.create<PlayerControls>());
                player->add(s.create<PlayerSpriteAnimation>());

                player->getTransformation().setScale({5, 5, 1});

                return player;
            }

            Entity* createNPC() {
                EntityComponentService& s = Services::GetEntityComponentService();

                Entity* npc = new Entity();
                Graphics* g = s.create<SpriteSheetGraphics>(Services::GetResources().loadOrGet<Texture>(
                        Services::GetPaths().getResourcePath() + "/img/Platformer/GreenBot16.png"
                ), 7, 4);
                g->setShader(spriteSheetShader);
                npc->add(g);
                npc->add(s.create<VelocityBehaviour>());
                npc->add(s.create<PlayerSpriteAnimation>());
                npc->add(s.create<DragNDrop>());

                npc->getTransformation().setScale({5, 5, 1});

                return npc;
            }

            Entity* createCamera(Entity *player) {
                LOG(INFO) << "Demo: create Camera";
                EntityComponentService& s = Services::GetEntityComponentService();

                Entity *cam = new Entity();
                cam->add(s.create<Camera>(
                        Services::GetFactory().create<Viewport>(),
                        std::make_shared<PixelScreenProjection>()
                ));
                cam->getTransformation().z() = 1;
                cam->add(s.create<FollowEntityBehaviour>(player));

                return cam;
            }

            Entity* createPlatform(int span) {
                LOG(INFO) << "Demo: createPlatform of size " << span;

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

                    block->getTransformation().x() = x;
                    block->getTransformation().setScale({scale, scale, 1});

                    block->setParent(platform);

                    tex = centerBlockTexture;
                }

                platform->add(s.create<Size>(glm::vec3(0, 0, 1)));
                FloatBoundingBox3D platformBoundingBox = platform->get<Size>()->toAbsoluteBoundingBox();
                platformBoundingBox.print();

                return platform;
            }

            void createEnvironment() {
                LOG(INFO) << "Demo: create Environment";
                EntityComponentService& s = Services::GetEntityComponentService();
                glm::ivec2 resolution = Engine::Instance().getWindow()->getResolution();
                Resources &r = Services::GetResources();
                Path imgPath = Services::GetPaths().getResourcePath() + "/img/Platformer";

                centerBlockTexture = r.loadOrGet<Texture>(imgPath + "/Block/Center.png");
                leftBlockTexture   = r.loadOrGet<Texture>(imgPath + "/Block/Left.png");
                rightBlockTexture  = r.loadOrGet<Texture>(imgPath + "/Block/Right.png");

                int w = centerBlockTexture->getWidth();
                int h = centerBlockTexture->getHeight();
                int y = resolution.y - 2*h;

                Entity *p1 = createPlatform(5);
                p1->getTransformation().position2D() = {0, -200};
                _mainLayer->spawn(p1);

                Entity *p2 = createPlatform(2);
                p2->getTransformation().position2D() = {300, 100};
                _mainLayer->spawn(p2);

                {
                    Entity *background = new Entity();
                    SpriteGraphics* backgroundGraphics = s.create<SpriteGraphics>(
                            r.loadOrGet<Texture>(imgPath + "/bg.png")
                    );
                    backgroundGraphics->setShader(spriteShader);
                    background->add(backgroundGraphics);

                    Entity *backgroundCam = new Entity();
                    backgroundCam->add(s.create<Camera>(
                            Services::GetFactory().create<Viewport>(),
                            std::make_shared<PixelScreenProjection>()
                    ));
                    backgroundCam->getTransformation().z() = 1;

                    WorldLayer *bg = new WorldLayer("Background", -10);
                    bg->spawn(background);
                    bg->spawn(backgroundCam);
                    _world->addLayer(bg);
                }
            }

        public:
            Demo() : Game()
            {

            }

            ~Demo() override {
                if (unregisterWorld(_world)) {
                    delete _world;
                } else {
                    LOG(ERROR) << "The world of JumpNRun could not be deleted!";
                }
            }

            virtual void initialize() override {
                Game::initialize();

                LOG(INFO) << "Demo: initialize";

                gatherResources();

                _mainLayer = new WorldLayer(PAX_WORLDLAYERNAME_MAIN, 2);

                _world = new World();
                _player = createPlayer();
                _camera = createCamera(_player);
                LOG(INFO) << "Demo: spawn Player";
                _mainLayer->spawn(_player);
                LOG(INFO) << "Demo: spawn Camera";
                _mainLayer->spawn(_camera);
                createEnvironment();

                Entity* npc = createNPC();
                npc->getTransformation().position2D() = {-20, -120};
                _mainLayer->spawn(npc);

                _world->addLayer(_mainLayer);
                setActiveWorld(_world);

                // test info
                std::cout << "\n"
                << "WorkingDirectory == " << Services::GetPaths().getWorkingDirectory() << "\n\n"
                << "    ResourcePath == " << Services::GetPaths().getResourcePath() << "\n\n" << std::endl;
            }
        };
    }
}

#endif //PAXENGINE3_JUMPNRUNDEMO_H
