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

#include "paxtiles/Tile.h"
#include "paxtiles/TileMap.h"
#include "paxtiles/TileMapProperty.h"

namespace PAX {
    namespace TileDemo {
        class Demo : public Game {
            // World
            World * world = nullptr;
            std::shared_ptr<WorldLayer> mainLayer = nullptr;

            // Entities
            Entity camera;

            // Resources
            std::shared_ptr<WorldLayerPrefab> mainLayerPrefab;

            void gatherResources() {
                mainLayerPrefab = Services::GetResources().loadOrGet<WorldLayerPrefab>(
                        Services::GetPaths().getResourcePath() + "/PlatformerDemo/prefabs/worldlayer/main.paxprefab.json"
                );
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
                gatherResources();
                Services::GetEventService().add<KeyPressedEvent, Demo, &Demo::onKeyDown>(this);
                std::cout << "[PAX::TileDemo::Demo::initialize] After gather resources" << std::endl;

                world = new World();
                mainLayer = mainLayerPrefab->create();

                camera.add(new Camera(
                        Services::GetFactoryService().get<ViewportFactory>()->create(),
                        std::make_shared<PixelScreenProjection>()
                        ));
                mainLayer->spawn(&camera);
                camera.getTransformation().z() = 10;

                world->addLayer(mainLayer.get());
                setActiveWorld(world);
            }

            void terminate() override {
                world->removeLayer(mainLayer.get());
                mainLayer.reset();
                Game::terminate();
            }
        };
    }
}

#endif //PAXENGINE3_PAXTILEDEMO_H
