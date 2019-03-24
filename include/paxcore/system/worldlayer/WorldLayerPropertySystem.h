//
// Created by Paul on 23.03.2019.
//

#ifndef PAXENGINE3_WORLDLAYERPROPERTYSYSTEM_H
#define PAXENGINE3_WORLDLAYERPROPERTYSYSTEM_H

#include "../WorldSystem.h"

namespace PAX {
    template<typename... RequiredProperties>
    class WorldLayerPropertySystem : public WorldSystem {
        std::map<World, WorldLayerManagerView<RequiredProperties...>> worldLayerProperties;

    public:
        void onWorldRegistered(WorldEvent & event) override {
            worldLayerProperties[event.world] = WorldLayerManagerView<RequiredProperties...>(world.getWorldLayerManager());
        }

        void onWorldUnregistered(WorldEvent & event) override {
            worldLayerProperties.erase(event.world);
        }

        const std::set<WorldLayer*> & getWorldLayers() const {
            return worldLayerProperties[WorldSystem::activeWorld].getContainers();
        }
    };
}

#endif //PAXENGINE3_WORLDLAYERPROPERTYSYSTEM_H
