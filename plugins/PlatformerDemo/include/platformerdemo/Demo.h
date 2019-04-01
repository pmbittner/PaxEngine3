//
// Created by Paul on 06.01.2018.
//

#ifndef PAXENGINE3_JUMPNRUNDEMO_H
#define PAXENGINE3_JUMPNRUNDEMO_H

#include <paxutil/io/Path.h>

#include <paxcore/Game.h>
#include <paxcore/Engine.h>
#include <paxcore/entity/property/Size.h>
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
            std::shared_ptr<Entity> player = nullptr;
            std::shared_ptr<Entity> npc = nullptr;
            Entity * camera = nullptr;

            // Resources
            std::shared_ptr<EntityPrefab> playerPrefab, npcPrefab;

            std::shared_ptr<Texture> centerBlockTexture;
            std::shared_ptr<Texture> leftBlockTexture;
            std::shared_ptr<Texture> rightBlockTexture;
            std::shared_ptr<Shader> spriteShader;

            // Settings
            struct {
                float
                camera = 10,
                platforms = 0;
            } depthFor;

            static constexpr float GlobalScale = 5;
            glm::vec3 GlobalScaleVec3;

            void gatherResources() {
                spriteShader = Services::GetResources().loadOrGet<Shader>(
                        Shader::FileInfo(
                                Services::GetPaths().getResourcePath() + "/shader/sprite/sprite.vert",
                                Services::GetPaths().getResourcePath() + "/shader/sprite/sprite.frag"
                        )
                );

                playerPrefab = Services::GetResources().loadOrGet<EntityPrefab>(
                        Services::GetPaths().getResourcePath() + "/PlatformerDemo/prefabs/entity/Player.paxprefab.json"
                );

                npcPrefab = Services::GetResources().loadOrGet<EntityPrefab>(
                        Services::GetPaths().getResourcePath() + "/PlatformerDemo/prefabs/entity/GreenGuy.paxprefab.json"
                );
            }

            Entity* createCamera(const std::shared_ptr<Entity> & player) {
                Entity *cam = new Entity();
                cam->add(new Camera(
                        // TODO: Enable use of custom type factories like this in prefabs.
                        Services::GetFactoryService().get<ViewportFactory>()->create(),
                        std::make_shared<PixelScreenProjection>()
                ));
                cam->getTransformation().z() = depthFor.camera;
                cam->add(new FollowEntityBehaviour(player.get()));

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

                    std::shared_ptr<TileMap> tileMap = res.loadOrGet<TileMap>(Services::GetPaths().getResourcePath() + "PlatformerDemo/tiled/SmallForest/SmallForest.json");
                    mainLayer->add(new TileMapProperty(tileMap));
                }//*/
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

                std::cout << "[PAX::PlatformerDemo::Demo::initialize] After gather resources" << std::endl;

                mainLayer = new WorldLayer("PlatformerDemo::MainLayer", 2);

                world = new World();
                player = playerPrefab->create();
                camera = createCamera(player);
                mainLayer->spawn(player.get());
                mainLayer->spawn(camera);
                createEnvironment();

                npc = npcPrefab->create();
                npc->getTransformation().position2D() = {-20, -120};
                mainLayer->spawn(npc.get());

                world->addLayer(mainLayer);
                setActiveWorld(world);
            }

            void terminate() override {
                player.reset();
                npc.reset();

                if (unregisterWorld(world, true)) {
                    delete world;
                } else {
                    LOG(ERROR) << "The world of JumpNRun could not be deleted!";
                }

                Game::terminate();
            }
        };
    }
}

#endif //PAXENGINE3_JUMPNRUNDEMO_H
