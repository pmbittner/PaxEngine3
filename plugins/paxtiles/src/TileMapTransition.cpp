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
        PAX_PROPERTY_IMPL(TileMapTransition)

        ClassMetadata TileMapTransition::getMetadata() {
            ClassMetadata m = Super::getMetadata();
            m.add(paxfieldalias("transition_target_map", targetMap)).flags = Field::IsMandatory;
            m.add(paxfieldalias("transition_target_id", targetTransitionID)).flags = Field::IsMandatory;
            return m;
        }

        TileMapTransition::TileMapTransition() = default;

        TileMapTransition::TileMapTransition(const PAX::Path &targetMap, int targetTransitionID)
        : targetMap(targetMap), targetTransitionID(targetTransitionID)
        {
        }

        void TileMapTransition::spawned() {
            Super::spawned();
            Services::GetEventService().add<KeyPressedEvent, TileMapTransition, &TileMapTransition::onKeyDown>(this);
        }

        void TileMapTransition::despawned() {
            Super::despawned();
            Services::GetEventService().remove<KeyPressedEvent, TileMapTransition, &TileMapTransition::onKeyDown>(this);
        }

        void TileMapTransition::onKeyDown(PAX::KeyPressedEvent &keyPressedEvent) {
            if (keyPressedEvent.repeated) return;

            if (keyPressedEvent.button == PAX::Key::T) {
                keyPressedEvent.consume();

                PAX_LOG(Log::Level::Info, "Transition initiated by entity " << getOwner());
                //PAX_PRINT_OUT("Transition to object " << targetTransitionID << " in " << targetMap)

                // TODO: Load a world instead of a layer.
                // TODO: Try to reuse worlds instead of reloading them all the time.
                std::shared_ptr<WorldLayerPrefab> worldLayerPrefab =
                        Services::GetResources().loadOrGet<WorldLayerPrefab>(targetMap);
                WorldLayer * targetWorldLayer = worldLayerPrefab->create({});

                //PAX_PRINT_OUT("Created target world")

                // Find location of target entity
                GameEntity * targetGameEntity = targetWorldLayer->getGameEntityIDService().getGameEntity(targetTransitionID);
                if (!targetGameEntity) {
                    PAX_LOG(Log::Level::Warn, "Could not detect target entity via id = " << targetTransitionID);
                    return;
                }
                glm::vec2 targetPos = targetGameEntity->getTransformation().position2D();

                // Transfer collided entites:
                // TODO: Find a way to not hardcode this. Especially for the camera!
                //*
                WorldLayer * sourceWorldLayer = getOwner()->getWorldLayer();
                GameEntity * player = sourceWorldLayer->getGameEntityIDService().getGameEntity(1001);
                GameEntity * cam    = sourceWorldLayer->getGameEntityIDService().getGameEntity(1002);
                sourceWorldLayer->despawn(cam);
                //PAX_PRINT_OUT("Despawned camera from source world")
                sourceWorldLayer->despawn(player);
                //PAX_PRINT_OUT("Despawned player from source world")
                 //*/

                //*
                targetWorldLayer->getGameEntityIDService().reserveIDFor(player, 1001);
                targetWorldLayer->getGameEntityIDService().reserveIDFor(cam, 1002);
                targetWorldLayer->spawn(player);
                player->getTransformation().position2D() = targetPos;
                //PAX_PRINT_OUT("Spawned player at target world")
                targetWorldLayer->spawn(cam);
                cam->getTransformation().position2D() = targetPos;
                //PAX_PRINT_OUT("Spawned camera at target world")
                //*/

                // Load new world
                //*
                World * targetWorld = new World();
                targetWorld->addLayer(targetWorldLayer);
                //PAX_PRINT_OUT("Switching active world")
                Engine::Instance().getGame()->setActiveWorld(targetWorld);
                //PAX_PRINT_OUT("Done")
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