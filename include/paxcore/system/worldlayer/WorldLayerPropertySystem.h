//
// Created by Paul on 23.03.2019.
//

#ifndef PAXENGINE3_WORLDLAYERPROPERTYSYSTEM_H
#define PAXENGINE3_WORLDLAYERPROPERTYSYSTEM_H

#include <map>
#include "../WorldSystem.h"

namespace PAX {
    template<typename... RequiredProperties>
    class WorldLayerPropertySystem : public WorldSystem {
        std::map<World*, WorldLayerManagerView<RequiredProperties...>> worldLayerProperties;

    public:
        void onWorldRegistered(WorldEvent & event) override {
            worldLayerProperties.emplace(event.world, event.world->getWorldLayerManager());
        }

        void onWorldUnregistered(WorldEvent & event) override {
            worldLayerProperties.erase(event.world);
        }

        PAX_NODISCARD const std::set<WorldLayer*> & getWorldLayers() const {
            return worldLayerProperties.at(WorldSystem::activeWorld).getEntities();
        }
    };
}

#endif //PAXENGINE3_WORLDLAYERPROPERTYSYSTEM_H
