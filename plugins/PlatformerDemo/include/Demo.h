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
#include <paxtiles/include/paxtiles/Tile.h>
#include <paxtiles/include/paxtiles/TileMap.h>
#include <paxtiles/include/paxtiles/TileMapProperty.h>

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

            std::shared_ptr<SpriteSheetGraphics> playerGraphics = nullptr;

            std::shared_ptr<Texture> centerBlockTexture;
            std::shared_ptr<Texture> leftBlockTexture;
            std::shared_ptr<Texture> rightBlockTexture;

            std::shared_ptr<Shader> spriteShader, spriteSheetShader;


            struct {
                float
                camera = 10,
                characters = 2,
                platforms = 0,
                tilemap = -1;
            } depthFor;

            void gatherResources() {
                LOG(INFO) << "Demo: gatherResources";

                AllocationService& s = Services::GetDefaultAllocationService();

                std::shared_ptr<Texture> spriteTest = Services::GetResources().loadOrGet<Texture>(
                        Services::GetPaths().getResourcePath() + "/img/Platformer/GreenBot16.png"
                );

                spriteShader = Services::GetResources().loadOrGet<Shader>(
                        Shader::FileInfo(
                                Services::GetPaths().getResourcePath() + "/shader/sprite/sprite.vert",
                                Services::GetPaths().getResourcePath() + "/shader/sprite/sprite.frag"
                        )
                );

                playerGraphics = s.create<SpriteSheetGraphics>(spriteTest, 7, 4);
                spriteSheetShader = Services::GetResources().loadOrGet<Shader>(
                        Shader::FileInfo(
                                Services::GetPaths().getResourcePath() + "/shader/sprite/sprite.vert",
                                Services::GetPaths().getResourcePath() + "/shader/sprite/sprite.frag"
                        ),
                        playerGraphics->getShaderFlags()
                );

                playerGraphics->setShader(spriteSheetShader);
            }

            Entity* createPlayer() {
                AllocationService& s = Services::GetDefaultAllocationService();

                Entity* player = new Entity();
                player->add(playerGraphics);
                player->add(s.create<VelocityBehaviour>());
                player->add(s.create<PlayerControls>());
                player->add(s.create<PlayerSpriteAnimation>());

                player->getTransformation().setScale({5, 5, 1});
                player->getTransformation().position().z = depthFor.characters;

                return player;
            }

            Entity* createNPC() {
                AllocationService& s = Services::GetDefaultAllocationService();

                Entity* npc = new Entity();
                std::shared_ptr<Graphics> g = s.create<SpriteSheetGraphics>(Services::GetResources().loadOrGet<Texture>(
                        Services::GetPaths().getResourcePath() + "/img/Platformer/GreenBot16.png"
                ), 7, 4);
                g->setShader(spriteSheetShader);
                npc->add(g);
                npc->add(s.create<VelocityBehaviour>());
                npc->add(s.create<PlayerSpriteAnimation>());

                npc->getTransformation().setScale({5, 5, 1});
                npc->getTransformation().position().z = depthFor.characters;

                return npc;
            }

            Entity* createCamera(Entity *player) {
                LOG(INFO) << "Demo: create Camera";
                AllocationService& s = Services::GetDefaultAllocationService();

                Entity *cam = new Entity();
                cam->add(s.create<Camera>(
                        Services::GetFactory().create<Viewport>(),
                        std::make_shared<PixelScreenProjection>()
                ));
                cam->getTransformation().z() = depthFor.camera;
                cam->add(s.create<FollowEntityBehaviour>(player));

                return cam;
            }

            Entity* createPlatform(int span) {
                LOG(INFO) << "Demo: createPlatform of size " << span;

                int scale = 5;
                AllocationService& s = Services::GetDefaultAllocationService();

                Entity* platform = new Entity();
                int w = centerBlockTexture->getWidth() * scale;
                int xMax = (span-1)*(w/2);

                std::shared_ptr<Texture> tex = leftBlockTexture;
                for (int x = -xMax; x <= xMax; x += w) {
                    if (x >= xMax)
                        tex = rightBlockTexture;

                    Entity *block = new Entity();
                    std::shared_ptr<SpriteGraphics> g = s.create<SpriteGraphics>(tex);
                    g->setShader(spriteShader);
                    block->add(g);

                    block->getTransformation().x() = x;
                    block->getTransformation().z() = 0;
                    block->getTransformation().setScale({scale, scale, 1});

                    block->setParent(platform);

                    tex = centerBlockTexture;
                }

                platform->getTransformation().z() = depthFor.platforms;

                platform->add(s.create<Size>(glm::vec3(0, 0, 1)));
                FloatBoundingBox3D platformBoundingBox = platform->get<Size>()->toAbsoluteBoundingBox();
                platformBoundingBox.print();

                return platform;
            }

            void createEnvironment() {
                LOG(INFO) << "Demo: create Environment";
                AllocationService& s = Services::GetDefaultAllocationService();
                glm::ivec2 resolution = Services::GetWindowService().getWindow()->getResolution();
                Resources &res = Services::GetResources();
                Path imgPath = Services::GetPaths().getResourcePath() + "/img";

                centerBlockTexture = res.loadOrGet<Texture>(imgPath + "/Platformer/Block/Center.png");
                leftBlockTexture   = res.loadOrGet<Texture>(imgPath + "/Platformer/Block/Left.png");
                rightBlockTexture  = res.loadOrGet<Texture>(imgPath + "/Platformer/Block/Right.png");

                int w = centerBlockTexture->getWidth();
                int h = centerBlockTexture->getHeight();
                int y = resolution.y - 2*h;

                {
                    Entity *p1 = createPlatform(5);
                    p1->getTransformation().position2D() = {0, -200};
                    _mainLayer->spawn(p1);
                }

                {
                    Entity *p2 = createPlatform(2);
                    p2->getTransformation().position2D() = {300, 100};
                    p2->add(s.create<DragNDrop>());
                    _mainLayer->spawn(p2);
                }

                { // create background in its own layer
                    Entity *background = new Entity();
                    std::shared_ptr<SpriteGraphics> backgroundGraphics = s.create<SpriteGraphics>(
                            res.loadOrGet<Texture>(imgPath + "/Platformer/bg.png")
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

                {
                    // create tile sheet test
                    using namespace Tiles;

                    TileMapProperty::initialize();

                    Tile grass = {6, 6};
                    Tile plant = {6, 0};
                    Tile u  = {3, 5};
                    Tile d  = {2, 0};
                    Tile l  = {5, 2};
                    Tile r  = {0, 2};
                    Tile ul = {1, 1};
                    Tile ur = {2, 1};
                    Tile dl = {1, 2};
                    Tile dr = {2, 2};

                    std::vector<std::vector<Tile>> tiles = {
                            { // row 0
                                ul, u, u, ur
                            },
                            {
                                l, grass, grass, r
                            },
                            {
                                l, grass, plant, r
                            },
                            {
                                dl, d, d, dr
                            }
                    };

                    TileMap tileMap;
                    tileMap.create(tiles, res.load<SpriteSheet>(imgPath + "/RPG/demotilesheet.png", 24, 12));
                    const auto& tileMapProperty = Services::GetDefaultAllocationService().create<TileMapProperty>(tileMap);
                    auto& entity = tileMapProperty->getTileMapEntity();
                    entity.getTransformation().z() = depthFor.tilemap;
                    _mainLayer->add(tileMapProperty);
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

            void onKeyDown(KeyPressedEvent & keyPressedEvent) {
                if (keyPressedEvent.button == PAX::Key::ESCAPE)
                    Engine::Instance().stop();
            }

            virtual void initialize() override {
                Game::initialize();

                Services::GetEventService().add<KeyPressedEvent, Demo, &Demo::onKeyDown>(this);
                
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
            }
        };
    }
}

#endif //PAXENGINE3_JUMPNRUNDEMO_H
