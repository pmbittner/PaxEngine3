//
// Created by Paul on 06.01.2018.
//

#ifndef PAXENGINE3_PAXTILEDEMO_H
#define PAXENGINE3_PAXTILEDEMO_H

#include <paxutil/io/Path.h>

#include <paxcore/Game.h>
#include <paxcore/Engine.h>
#include <paxcore/entity/property/Size.h>
#include <paxcore/rendering/camera/FullPixelScreenProjection.h>
#include <paxcore/rendering/data/SpriteSheet.h>
#include <paxcore/rendering/graphics/SpriteGraphics.h>
#include <paxcore/rendering/graphics/SpriteSheetGraphics.h>
#include <paxcore/rendering/factory/ViewportFactory.h>
#include <paxcore/io/event/KeyPressedEvent.h>
#include <paxcore/entity/property/behaviours/2d/FollowEntityBehaviour.h>

#include "paxtiles/Tile.h"
#include "paxtiles/TileMap.h"
#include "paxtiles/TileMapProperty.h"

#include "paxutil/log/Log.h"

namespace PAX {
    namespace TileDemo {
        class Demo : public Game {
            World * world = nullptr;

        public:
            Demo() : Game()
            {
                PAX_PRINT_OUT("Moinsen " << 24)
                PAX_PRINT_OUT_DEBUG("I am only visible in debug mode hihi.")
            }

            void onKeyDown(KeyPressedEvent & keyPressedEvent) {
                if (keyPressedEvent.button == PAX::Key::ESCAPE)
                    Engine::Instance().stop();
            }

            void initialize() override {
                Game::initialize();
                Services::GetEventService().add<KeyPressedEvent, Demo, &Demo::onKeyDown>(this);

                std::shared_ptr<WorldLayerPrefab> worldLayerPrefab = Services::GetResources().loadOrGet<WorldLayerPrefab>(
                        Services::GetPaths().getResourcePath() + "/TileDemo/worlds/main/mainlayer.paxprefab.json"
                );

                PAX_PRINT_OUT("Create World")
                world = new World();
                WorldLayer * mainLayer = worldLayerPrefab->create();
                PAX_PRINT_OUT("Done")

                /*
                camera.add(new Camera(
                        Services::GetFactoryService().get<ViewportFactory>()->create(),
                        std::make_shared<PixelScreenProjection>()
                        ));
                mainLayer->spawn(&camera);
                camera.getTransformation().z() = 10;

                glenys = glenysPrefab->create();
                FollowEntityBehaviour * followEntityBehaviour = new FollowEntityBehaviour(glenys.get());
                followEntityBehaviour->shouldRespectWorldSize(true);
                camera.add(followEntityBehaviour);
                mainLayer->spawn(glenys.get());
                 */

                world->addLayer(mainLayer);
                setActiveWorld(world);

                PAX_PRINT_OUT("Done")
            }

            void terminate() override {
                //world->removeLayer(mainLayer.get());
                //glenys.reset();
                //mainLayer.reset();
                Game::terminate();
            }
        };
    }
}

#endif //PAXENGINE3_PAXTILEDEMO_H
