//
// Created by Paul on 24.03.2019.
//

#ifndef PAXENGINE3_ENTITYPROPERTYSYSTEM_H
#define PAXENGINE3_ENTITYPROPERTYSYSTEM_H

#include <unordered_map>

#include <paxutil/property/PropertyContainerManagerView.h>
#include <paxcore/system/WorldSystem.h>

namespace PAX {
    template<typename... RequiredProperties>
    class EntityPropertySystem : public WorldSystem {
        const static WorldLayerSort worldLayerSorter;

        std::unordered_map<World*, std::unordered_map<WorldLayer*, EntityManagerView<RequiredProperties...>>> entities;
        std::vector<WorldLayer*> layers;

    public:
        void onWorldRegistered(WorldEvent &event) override {
            for (WorldLayer * worldLayer : event.world->getLayers()) {
                WorldLayerAddedEvent e(event.world, worldLayer);
                onWorldLayerAdded(e);
            }

            event.world->getEventService().add<WorldLayerAddedEvent,   EntityPropertySystem, &EntityPropertySystem::onWorldLayerAdded>(this);
            event.world->getEventService().add<WorldLayerRemovedEvent, EntityPropertySystem, &EntityPropertySystem::onWorldLayerRemoved>(this);
        }

        void onWorldUnregistered(WorldEvent & event) override {
            for (WorldLayer * worldLayer : event.world->getLayers()) {
                WorldLayerRemovedEvent e(event.world, worldLayer);
                onWorldLayerRemoved(e);
            }

            event.world->getEventService().remove<WorldLayerAddedEvent, EntityPropertySystem, &EntityPropertySystem::onWorldLayerAdded>(this);
            event.world->getEventService().remove<WorldLayerRemovedEvent, EntityPropertySystem, &EntityPropertySystem::onWorldLayerRemoved>(this);
        }

        void onWorldLayerAdded(WorldLayerAddedEvent &event) {
            layers.push_back(event.worldLayer);
            std::sort(layers.begin(), layers.end(), worldLayerSorter);

            const EntityManager & manager = event.worldLayer->getEntityManager();
            //EntityManagerView<RequiredProperties...> view(manager);

            entities[event.world].emplace(event.worldLayer, manager);
        }

        void onWorldLayerRemoved(WorldLayerRemovedEvent &event) {
            Util::removeFromVector(layers, event.worldLayer);
            entities[event.world].erase(event.worldLayer);
        }

        const std::vector<WorldLayer*> & getWorldLayers() {
            return layers;
        }

        const std::set<Entity*> & getEntities(WorldLayer * worldLayer) {
            auto & m = entities[WorldSystem::activeWorld];
            const auto & it = m.find(worldLayer);

            if (it != m.end()) {
                return it->second.getContainers();
            }

            PAX_THROW_RUNTIME_ERROR("[EntityPropertySystem::getEntities] Could not obtain Entities for WorldLayer " << worldLayer)
        }
    };

    template<typename... RequiredProperties>
    const WorldLayerSort EntityPropertySystem<RequiredProperties...>::worldLayerSorter;
}

#endif //PAXENGINE3_ENTITYPROPERTYSYSTEM_H
