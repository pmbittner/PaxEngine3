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
        public:
            Demo() : Game()
            {
                PAX_LOG(PAX::Log::Level::Info, "Moinsen " << 24);
                PAX_LOG_DEBUG(PAX::Log::Level::Info, "I am only visible in debug mode hihi.");
            }

            void onKeyDown(KeyPressedEvent & keyPressedEvent) {
                if (keyPressedEvent.button == PAX::Key::ESCAPE)
                    Engine::Instance().stop();
            }

            void initialize() override {
                Game::initialize();
                Services::GetEventService().add<KeyPressedEvent, Demo, &Demo::onKeyDown>(this);

                Settings gameSettings(Services::GetPaths().getResourcePath() + "/TileDemo/game.paxconfig");
                Path startWorldPath = gameSettings.get("startworld");

                PAX_LOG(PAX::Log::Level::Info, "Create World");
                std::shared_ptr<WorldLayerPrefab> worldLayerPrefab =
                        Services::GetResources().loadOrGet<WorldLayerPrefab>(startWorldPath);

                World * world = new World();
                world->addLayer(worldLayerPrefab->create({}));
                setActiveWorld(world);

                PAX_LOG(PAX::Log::Level::Info, "Done");
            }

            void terminate() override {
                Game::terminate();
            }
        };
    }
}

#endif //PAXENGINE3_PAXTILEDEMO_H
