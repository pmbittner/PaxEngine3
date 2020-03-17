//
// Created by Paul on 24.03.2019.
//

#ifndef PAXENGINE3_GAMEENTITYPROPERTYSYSTEM_H
#define PAXENGINE3_GAMEENTITYPROPERTYSYSTEM_H

#include <unordered_map>

#include <polypropylene/property/EntityManagerView.h>
#include <paxcore/system/WorldSystem.h>

namespace PAX {
    template<typename... RequiredProperties>
    class GameEntityPropertySystem : public WorldSystem {
        std::unordered_map<World*, GameEntityManagerView<RequiredProperties...>> entities;

    public:
        void onWorldRegistered(WorldEvent &event) override {
            const GameEntityManager & manager = event.world->getGameEntityManager();
            entities.emplace(event.world, manager);
        }

        void onWorldUnregistered(WorldEvent & event) override {
            entities.erase(event.world);
        }

        PAX_NODISCARD const std::set<GameEntity*> & getEntities(World * world) {
            // TODO: Make safe
            return entities.at(world).getEntities();

            //PAX_THROW_RUNTIME_ERROR("Could not obtain Entities for WorldLayer " << worldLayer);
        }

        PAX_NODISCARD const std::set<GameEntity*> & getEntities() {
            return getEntities(WorldSystem::getActiveWorld());
        }
    };
}

#endif //PAXENGINE3_GAMEENTITYPROPERTYSYSTEM_H
