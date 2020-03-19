//
// Created by Paul on 06.01.2018.
//

#ifndef PAXENGINE3_PAXTILEDEMO_H
#define PAXENGINE3_PAXTILEDEMO_H

#include <paxcore/Game.h>
#include <paxcore/Engine.h>
#include <paxcore/io/event/KeyPressedEvent.h>

#include "polypropylene/log/Log.h"

#include <paxcore/gameentity/GameEntity.h>
#include <paxcore/gameentity/property/behaviours/NoClipControls.h>

#include <paxcore/rendering/graphics/SceneGraphGraphics.h>
#include <paxcore/rendering/geometry/ScreenFillingQuad.h>

#include <paxcore/rendering/factory/ViewportFactory.h>

namespace PAX {
    namespace Meshfold {
        class Meshfold : public Game {
            World * world = nullptr;
            Settings settings;

        public:
            void initialize() override {
                Game::initialize();
                settings.parse(Services::GetPaths().getResourcePath() + "Meshfold/meshfold.paxconfig");
                std::shared_ptr<WorldPrefab> worldPrefab = Services::GetResources().loadOrGet<WorldPrefab>(
                        settings.get<Path>("StartWorld"));
                world = worldPrefab->create({});

                /// Spawn player
                {
                    Path playerPrefabPath = settings.get("playerprefab");
                    std::shared_ptr<GameEntityPrefab> playerPrefab =
                            Services::GetResources().loadOrGet<GameEntityPrefab>(playerPrefabPath);
                    GameEntity * player = playerPrefab->create({});
                    player->addTag(Tags::Player);

                    world->spawn(player);
                }

                setActiveWorld(world);
            }
        };
    }
}

#endif //PAXENGINE3_PAXTILEDEMO_H
