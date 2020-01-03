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
        const static WorldLayerSort worldLayerSorter;

        std::unordered_map<World*, std::unordered_map<WorldLayer*, GameEntityManagerView<RequiredProperties...>>> entities;
        std::unordered_map<World*, std::vector<WorldLayer*>> layers;

    public:
        void onWorldRegistered(WorldEvent &event) override {
            for (WorldLayer * worldLayer : event.world->getLayers()) {
                WorldLayerAddedEvent e(event.world, worldLayer);
                onWorldLayerAdded(e);
            }

            event.world->getEventService().add<WorldLayerAddedEvent,   GameEntityPropertySystem, &GameEntityPropertySystem::onWorldLayerAdded>(this);
            event.world->getEventService().add<WorldLayerRemovedEvent, GameEntityPropertySystem, &GameEntityPropertySystem::onWorldLayerRemoved>(this);
        }

        void onWorldUnregistered(WorldEvent & event) override {
            for (WorldLayer * worldLayer : event.world->getLayers()) {
                WorldLayerRemovedEvent e(event.world, worldLayer);
                onWorldLayerRemoved(e);
            }

            event.world->getEventService().remove<WorldLayerAddedEvent, GameEntityPropertySystem, &GameEntityPropertySystem::onWorldLayerAdded>(this);
            event.world->getEventService().remove<WorldLayerRemovedEvent, GameEntityPropertySystem, &GameEntityPropertySystem::onWorldLayerRemoved>(this);
        }

        void onWorldLayerAdded(WorldLayerAddedEvent &event) {
            layers[event.world].push_back(event.worldLayer);
            std::sort(layers[event.world].begin(), layers[event.world].end(), worldLayerSorter);

            const GameEntityManager & manager = event.worldLayer->getGameEntityManager();
            //GameEntityManagerView<RequiredProperties...> view(manager);

            entities[event.world].emplace(event.worldLayer, manager);
        }

        void onWorldLayerRemoved(WorldLayerRemovedEvent &event) {
            Util::removeFromVector(layers[event.world], event.worldLayer);
            entities[event.world].erase(event.worldLayer);
        }

        PAX_NODISCARD const std::vector<WorldLayer*> & getWorldLayers() {
            return layers[activeWorld];
        }

        PAX_NODISCARD const std::set<GameEntity*> & getEntities(WorldLayer * worldLayer) {
            auto & m = entities[WorldSystem::activeWorld];
            const auto & it = m.find(worldLayer);

            if (it != m.end()) {
                return it->second.getContainers();
            }

            PAX_THROW_RUNTIME_ERROR("Could not obtain Entities for WorldLayer " << worldLayer);
        }
    };

    template<typename... RequiredProperties>
    const WorldLayerSort GameEntityPropertySystem<RequiredProperties...>::worldLayerSorter;
}

#endif //PAXENGINE3_GAMEENTITYPROPERTYSYSTEM_H
