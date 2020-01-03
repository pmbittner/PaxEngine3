//
// Created by Paul on 06.01.2018.
//

#ifndef PAXENGINE3_JUMPNRUNDEMO_H
#define PAXENGINE3_JUMPNRUNDEMO_H

#include <polypropylene/io/Path.h>

#include <paxcore/Game.h>
#include <paxcore/Engine.h>
#include <paxcore/entity/property/Size.h>
#include <paxcore/rendering/camera/FullPixelScreenProjection.h>
#include <paxcore/rendering/data/SpriteSheet.h>
#include <paxcore/rendering/graphics/SpriteGraphics.h>
#include <paxcore/rendering/graphics/SpriteSheetGraphics.h>
#include <paxcore/rendering/factory/ViewportFactory.h>
#include <paxphysics/2d/shape/Rectangle.h>
#include <paxphysics/2d/box2d/Box2DHitbox.h>

#include "paxtiles/Tile.h"
#include "paxtiles/TileMap.h"
#include "paxtiles/TileMapProperty.h"

#include "behaviour/DragNDrop.h"
#include "behaviour/ProfileGameLoopBehaviour.h"

#include "behaviour/PlayerControls.h"
#include "behaviour/PlayerSpriteAnimation.h"
#include "paxcore/entity/property/behaviours/2d/FollowGameEntityBehaviour.h"

namespace PAX {
    namespace PlatformerDemo {
        class Demo : public Game {
            // World
            World * world = nullptr;
            WorldLayer* mainLayer = nullptr;

            // Resources
            std::shared_ptr<Texture> centerBlockTexture;
            std::shared_ptr<Texture> leftBlockTexture;
            std::shared_ptr<Texture> rightBlockTexture;
            std::shared_ptr<Shader> spriteShader;

            // Settings
            struct {
                float
                platforms = 0;
            } depthFor;

            void gatherResources() {
                spriteShader = Services::GetResources().loadOrGet<Shader>(
                        Shader::FileInfo(
                                Services::GetPaths().getResourcePath() + "/shader/sprite/sprite.vert",
                                Services::GetPaths().getResourcePath() + "/shader/sprite/sprite.frag"
                        )
                );
            }

            GameEntity* createPlatform(int span) {
                GameEntity* platform = new GameEntity();
                platform->i_setMotionType(MotionType::Static);
                float w = centerBlockTexture->getWidth();
                float xMax = (span-1)*(w/2);

                std::shared_ptr<Texture> tex = leftBlockTexture;
                for (float x = -xMax; x <= xMax; x += w) {
                    if (x >= xMax)
                        tex = rightBlockTexture;

                    GameEntity *block = new GameEntity();
                    block->i_setMotionType(MotionType::Static);
                    SpriteGraphics * g = new SpriteGraphics(tex);
                    g->setShader(spriteShader);
                    block->add(g);

                    block->getTransformation().x() = x;
                    block->getTransformation().z() = 0;

                    block->setParent(platform);

                    tex = centerBlockTexture;
                }

                platform->getTransformation().z() = depthFor.platforms;
                platform->add(new Size(glm::vec3(0, 0, 1)));

                FloatBoundingBox3D aabb = platform->get<Size>()->toAbsoluteBoundingBox();
                Physics::Hitbox2D * hitbox = new Physics::Box2DHitbox();
                //hitbox->setShape(std::make_unique<Physics::Rectangle>(glm::vec2(aabb.getLength(0), aabb.getLength(1))));
                hitbox->setFixtures({
                   Physics::Fixture2D(
                           std::make_shared<Physics::Rectangle>(glm::vec2(aabb.getLength(0), aabb.getLength(1))),
                           std::make_shared<Physics::PhysicsMaterial>()
                   )
                });
                platform->add(hitbox);

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
                    GameEntity *p1 = createPlatform(5);
                    p1->getTransformation().position2D() = {0, -40};
                    mainLayer->spawn(p1);
                }

                {
                    GameEntity *p2 = createPlatform(2);
                    p2->getTransformation().position2D() = {60, 20};
                    p2->add(new DragNDrop());
                    mainLayer->spawn(p2);
                }

                { // create background in its own layer
                    GameEntity *background = new GameEntity();
                    SpriteGraphics * backgroundGraphics = new SpriteGraphics(
                            res.loadOrGet<Texture>(imgPath + "/bg.png")
                    );
                    backgroundGraphics->setShader(spriteShader);
                    background->add(backgroundGraphics);

                    GameEntity *backgroundCam = new GameEntity();
                    backgroundCam->add(new Camera(
                            Services::GetFactoryService().get<ViewportFactory>()->create(),
                            std::make_shared<PixelScreenProjection>()
                    ));
                    backgroundCam->getTransformation().z() = 1;

                    WorldLayer *bg = new WorldLayer("Background", 2, -10);
                    bg->spawn(background);
                    bg->spawn(backgroundCam);
                    world->addLayer(bg);
                }
            }

        public:
            Demo() : Game()
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

                mainLayer = Services::GetResources().loadOrGet<WorldLayerPrefab>(
                        Services::GetPaths().getResourcePath() + "PlatformerDemo/prefabs/world/mainlayer.paxprefab.json"
                        )->create({});

                world = new World();
                createEnvironment();

                world->addLayer(mainLayer);
                setActiveWorld(world);
            }
        };
    }
}

#endif //PAXENGINE3_JUMPNRUNDEMO_H
