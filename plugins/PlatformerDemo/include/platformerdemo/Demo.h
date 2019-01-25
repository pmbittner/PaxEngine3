//
// Created by Paul on 06.01.2018.
//

#ifndef PAXENGINE3_JUMPNRUNDEMO_H
#define PAXENGINE3_JUMPNRUNDEMO_H

#include <paxutil/io/Path.h>

#include <paxcore/Game.h>
#include <paxcore/Engine.h>
#include <paxcore/entity/component/Size.h>
#include <paxcore/rendering/camera/FullPixelScreenProjection.h>
#include <paxcore/rendering/data/SpriteSheet.h>
#include <paxcore/rendering/graphics/SpriteGraphics.h>
#include <paxcore/rendering/graphics/SpriteSheetGraphics.h>
#include <paxcore/rendering/factory/ViewportFactory.h>

#include "paxtiles/Tile.h"
#include "paxtiles/TileMap.h"
#include "paxtiles/TileMapProperty.h"

#include "behaviour/DragNDrop.h"
#include "behaviour/ProfileGameLoopBehaviour.h"

#include "behaviour/PlayerControls.h"
#include "behaviour/PlayerSpriteAnimation.h"
#include "behaviour/FollowEntityBehaviour.h"

namespace PAX {
    namespace PlatformerDemo {
        class Demo : public Game {
            // World
            World * world = nullptr;
            WorldLayer * mainLayer = nullptr;

            // Entities
            Entity * player = nullptr;
            Entity * camera = nullptr;

            // Properties
            Graphics * playerGraphics = nullptr;

            // Resources
            std::shared_ptr<Texture> centerBlockTexture;
            std::shared_ptr<Texture> leftBlockTexture;
            std::shared_ptr<Texture> rightBlockTexture;
            std::shared_ptr<Shader> spriteShader, spriteSheetShader;

            // Settings
            struct {
                float
                camera = 10,
                characters = 2,
                platforms = 0,
                tilemap = -1;
            } depthFor;

            static constexpr float GlobalScale = 5;
            glm::vec3 GlobalScaleVec3;

            void gatherResources() {
                std::shared_ptr<Texture> spriteTest = Services::GetResources().loadOrGet<Texture>(
                        Services::GetPaths().getResourcePath() + "/PlatformerDemo/img/GreenBot16.png"
                );

                spriteShader = Services::GetResources().loadOrGet<Shader>(
                        Shader::FileInfo(
                                Services::GetPaths().getResourcePath() + "/shader/sprite/sprite.vert",
                                Services::GetPaths().getResourcePath() + "/shader/sprite/sprite.frag"
                        )
                );

                playerGraphics = new SpriteSheetGraphics(spriteTest, 7, 4);

                spriteSheetShader = Services::GetResources().loadOrGet<Shader>(
                        Shader::FileInfo(
                                Services::GetPaths().getResourcePath() + "/shader/sprite/sprite.vert",
                                Services::GetPaths().getResourcePath() + "/shader/sprite/sprite.frag"
                        ),
                        playerGraphics->getShaderFlags() // NOTICE: THis is important and has to be considered in prefab later on!
                );

                playerGraphics->setShader(spriteSheetShader);
            }

            Entity* createPlayer() {
                Entity* player = new Entity();
                player->add(playerGraphics);
                player->add(new VelocityBehaviour());
                player->add(new PlayerControls());
                player->add(new PlayerSpriteAnimation());

                player->getTransformation().setScale(GlobalScaleVec3);
                player->getTransformation().position().z = depthFor.characters;

                return player;
            }

            Entity* createNPC() {
                Entity* npc = new Entity();

                npc->add(new SpriteSheetGraphics(Services::GetResources().loadOrGet<Texture>(
                        Services::GetPaths().getResourcePath() + "/PlatformerDemo/img/GreenBot16.png"
                ), 7, 4));
                npc->add(new VelocityBehaviour());
                npc->add(new PlayerSpriteAnimation());
                npc->add(new ProfileGameLoopBehaviour());

                npc->getTransformation().setScale(GlobalScaleVec3);
                npc->getTransformation().position().z = depthFor.characters;

                npc->get<Graphics>()->setShader(spriteSheetShader);

                return npc;
            }

            Entity* createCamera(Entity *player) {
                Entity *cam = new Entity();
                cam->add(new Camera(
                        Services::GetFactoryService().get<ViewportFactory>()->create(),
                        std::make_shared<PixelScreenProjection>()
                ));
                cam->getTransformation().z() = depthFor.camera;
                cam->add(new FollowEntityBehaviour(player));

                return cam;
            }

            Entity* createPlatform(int span) {
                Entity* platform = new Entity();
                float w = centerBlockTexture->getWidth() * GlobalScale;
                float xMax = (span-1)*(w/2);

                std::shared_ptr<Texture> tex = leftBlockTexture;
                for (float x = -xMax; x <= xMax; x += w) {
                    if (x >= xMax)
                        tex = rightBlockTexture;

                    Entity *block = new Entity();
                    SpriteGraphics * g = new SpriteGraphics(tex);
                    g->setShader(spriteShader);
                    block->add(g);

                    block->getTransformation().x() = x;
                    block->getTransformation().z() = 0;
                    block->getTransformation().setScale(GlobalScaleVec3);

                    block->setParent(platform);

                    tex = centerBlockTexture;
                }

                platform->getTransformation().z() = depthFor.platforms;

                platform->add(new Size(glm::vec3(0, 0, 1)));
                FloatBoundingBox3D platformBoundingBox = platform->get<Size>()->toAbsoluteBoundingBox();

                return platform;
            }

            void createEnvironment() {
                glm::ivec2 resolution = Services::GetWindowService().getWindow()->getResolution();
                Resources &res = Services::GetResources();
                Path imgPath = Services::GetPaths().getResourcePath() + "/PlatformerDemo/img/";

                centerBlockTexture = res.loadOrGet<Texture>(imgPath + "/Block/Center.png");
                leftBlockTexture   = res.loadOrGet<Texture>(imgPath + "/Block/Left.png");
                rightBlockTexture  = res.loadOrGet<Texture>(imgPath + "/Block/Right.png");

                int w = centerBlockTexture->getWidth();
                int h = centerBlockTexture->getHeight();
                int y = resolution.y - 2*h;

                {
                    Entity *p1 = createPlatform(5);
                    p1->getTransformation().position2D() = {0, -200};
                    mainLayer->spawn(p1);
                }

                {
                    Entity *p2 = createPlatform(2);
                    p2->getTransformation().position2D() = {300, 100};
                    p2->add(new DragNDrop());
                    mainLayer->spawn(p2);
                }

                { // create background in its own layer
                    Entity *background = new Entity();
                    SpriteGraphics * backgroundGraphics = new SpriteGraphics(
                            res.loadOrGet<Texture>(imgPath + "/bg.png")
                    );
                    backgroundGraphics->setShader(spriteShader);
                    background->add(backgroundGraphics);

                    Entity *backgroundCam = new Entity();
                    backgroundCam->add(new Camera(
                            Services::GetFactoryService().get<ViewportFactory>()->create(),
                            std::make_shared<PixelScreenProjection>()
                    ));
                    backgroundCam->getTransformation().z() = 1;

                    WorldLayer *bg = new WorldLayer("Background", -10);
                    bg->spawn(background);
                    bg->spawn(backgroundCam);
                    world->addLayer(bg);
                }

                {
                    // create tile sheet test
                    using namespace Tiles;

                    TileMapProperty::initialize();

                    Tile grass = {6, 6};
                    Tile plant = {6, 0};
                    Tile dreck = {6, 5};
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
                                ul, u, u, u, ur
                            },
                            {
                                l, grass, grass, dreck, r
                            },
                            {
                                l, grass, plant, grass, r
                            },
                            {
                                dl, d, d, d, dr
                            }
                    };

                    TileMap tileMap;
                    tileMap.create(tiles, res.load<SpriteSheet>(imgPath + "/RPG/demotilesheet.png", 24, 12));
                    TileMapProperty * tileMapProperty = new TileMapProperty(tileMap);
                    auto& entity = tileMapProperty->getTileMapEntity();
                    entity.getTransformation().z() = depthFor.tilemap;
                    entity.getTransformation().setScale(entity.getTransformation().getScale() * GlobalScaleVec3);
                    mainLayer->add(tileMapProperty);
                }
            }

        public:
            Demo() : Game(), GlobalScaleVec3(GlobalScale, GlobalScale, 1)
            {

            }

            void onKeyDown(KeyPressedEvent & keyPressedEvent) {
                if (keyPressedEvent.button == PAX::Key::ESCAPE)
                    Engine::Instance().stop();
            }

            void initialize() override {
                Game::initialize();

                Services::GetEventService().add<KeyPressedEvent, Demo, &Demo::onKeyDown>(this);

                gatherResources();

                mainLayer = new WorldLayer("PlatformerDemo::MainLayer", 2);

                world = new World();
                player = createPlayer();
                camera = createCamera(player);
                mainLayer->spawn(player);
                mainLayer->spawn(camera);
                createEnvironment();

                Entity* npc = createNPC();
                npc->getTransformation().position2D() = {-20, -120};
                mainLayer->spawn(npc);

                world->addLayer(mainLayer);
                setActiveWorld(world);
            }

            void terminate() override {
                if (unregisterWorld(world, true)) {
                    delete world;
                } else {
                    LOG(ERROR) << "The world of JumpNRun could not be deleted!";
                }
            }
        };
    }
}

#endif //PAXENGINE3_JUMPNRUNDEMO_H
