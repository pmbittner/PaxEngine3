//
// Created by Paul on 02.07.2019.
//

#include <paxtiles/TileMapTransition.h>
#include <paxcore/service/Services.h>
#include <paxcore/io/event/KeyPressedEvent.h>
#include <paxcore/world/World.h>

#include <paxcore/Engine.h>
#include <paxcore/Game.h>

namespace PAX {
    namespace Tiles {
        PAX_PROPERTY_SOURCE(TileMapTransition, PAX_PROPERTY_IS_CONCRETE)

        TileMapTransition::This * TileMapTransition::createFromProvider(PAX::ContentProvider & c) {
            return new TileMapTransition(c.require<Path>("transition_target_map"), c.require<int>("transition_target_id"));
        }

        void TileMapTransition::initializeFromProvider(PAX::ContentProvider & c) {
            Super::initializeFromProvider(c);
        }

        TileMapTransition::TileMapTransition(const PAX::Path &targetMap, int targetTransitionID)
        : targetMap(targetMap), targetTransitionID(targetTransitionID)
        {
        }

        void TileMapTransition::attached(PAX::Entity &e) {
            Services::GetEventService().add<KeyPressedEvent, TileMapTransition, &TileMapTransition::onKeyDown>(this);
        }

        void TileMapTransition::detached(PAX::Entity &e) {
            Services::GetEventService().remove<KeyPressedEvent, TileMapTransition, &TileMapTransition::onKeyDown>(this);
        }

        void TileMapTransition::onKeyDown(PAX::KeyPressedEvent &keyPressedEvent) {
            if (keyPressedEvent.button == PAX::Key::T) {
                keyPressedEvent.consume();

                PAX_PRINT_OUT("Transition to object " << targetTransitionID << " in " << targetMap)

                // TODO: Load a world instead of a layer.
                std::shared_ptr<WorldLayerPrefab> worldLayerPrefab =
                        Services::GetResources().loadOrGet<WorldLayerPrefab>(targetMap);
                WorldLayer * targetWorldLayer = worldLayerPrefab->create({});

                PAX_PRINT_OUT("Created target world")

                // Transfer collided entites:
                // TODO: Find a way to not hardcode this. Especially for the camera!
                //*
                WorldLayer * sourceWorldLayer = getOwner()->getWorldLayer();
                Entity * player = sourceWorldLayer->getEntityIDService().getEntity(1001);
                Entity * cam    = sourceWorldLayer->getEntityIDService().getEntity(1002);
                sourceWorldLayer->despawn(cam);
                PAX_PRINT_OUT("Despawned camera from source world")
                sourceWorldLayer->despawn(player);
                PAX_PRINT_OUT("Despawned player from source world")
                 //*/

                //*
                targetWorldLayer->getEntityIDService().reserveIDFor(player, 1001);
                targetWorldLayer->getEntityIDService().reserveIDFor(cam, 1002);
                targetWorldLayer->spawn(player);
                PAX_PRINT_OUT("Spawned player at target world")
                targetWorldLayer->spawn(cam);
                PAX_PRINT_OUT("Spawned camera at target world")
                //*/

                // Load new world
                //*
                World * targetWorld = new World();
                targetWorld->addLayer(targetWorldLayer);
                PAX_PRINT_OUT("Switching active world")
                Engine::Instance().getGame()->setActiveWorld(targetWorld);
                PAX_PRINT_OUT("Done")
                //*/

                // Delete the old one because we can't handle caching so far.
                //*
                Engine::Instance().getGame()->unregisterWorld(sourceWorldLayer->getWorld());
                delete sourceWorldLayer->getWorld();
                //*/
            }
        }
    }
}