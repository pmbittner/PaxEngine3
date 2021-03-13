//
// Created by Paul on 24.03.2019.
//

#ifndef PAXENGINE3_GAMEENTITYPROPERTYSYSTEM_H
#define PAXENGINE3_GAMEENTITYPROPERTYSYSTEM_H

#include <unordered_map>
#include <paxcore/system/GameSystem.h>

namespace PAX {
    template<typename... RequiredProperties>
    class GameEntityPropertySystem : public GameSystem {
        std::unordered_map<World*, GameEntityManagerView<RequiredProperties...>> entities;

    public:
        void onWorldAdded(WorldEvent &event) override {
            const GameEntityManager & manager = event.world->getGameEntityManager();
            entities.emplace(event.world, manager);
        }

        void onWorldRemoved(WorldEvent & event) override {
            entities.erase(event.world);
        }

        PAX_NODISCARD const std::vector<GameEntity*> & getEntities(World * world) {
            // TODO: Make safe
            return entities.at(world).getEntities();
        }
    };
}

#endif //PAXENGINE3_GAMEENTITYPROPERTYSYSTEM_H
