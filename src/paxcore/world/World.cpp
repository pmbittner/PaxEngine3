//
// Created by Paul on 28.05.2017.
//

#include <paxcore/world/World.h>

namespace PAX {
    WorldLayerEvent::WorldLayerEvent(PAX::World *world, PAX::WorldLayer *worldLayer) : world(world), worldLayer(worldLayer) {}
    WorldLayerAddedEvent::WorldLayerAddedEvent(PAX::World *world, PAX::WorldLayer *worldLayer) : WorldLayerEvent(world, worldLayer) {}
    WorldLayerRemovedEvent::WorldLayerRemovedEvent(PAX::World *world, PAX::WorldLayer *worldLayer) : WorldLayerEvent(world, worldLayer) {}

    World::World() : worldLayers(localEventService) {

    }

    World::~World() = default;

    void World::addLayer(WorldLayer *layer) {
        if (worldLayers.add(layer)) {
            sceneGraph.addChild(layer->getSceneGraph().get());
            layer->getEventService().setParent(&localEventService);

            WorldLayerAddedEvent e(this, layer);
            localEventService(e);
        }
    }

    void World::removeLayer(WorldLayer *layer) {
        if (worldLayers.remove(layer)) {
            sceneGraph.removeChild(layer->getSceneGraph().get());
            layer->getEventService().setParent(nullptr);

            WorldLayerRemovedEvent e(this, layer);
            localEventService(e);
        }
    }

    const std::set<WorldLayer*>& World::getLayers() {
        return worldLayers.getPropertyContainers();
    }

    const PropertyContainerManager<WorldLayer>& World::getWorldLayerManager() const {
        return worldLayers;
    }

    WorldLayer* World::getWorldLayerWithName(const std::string &name) {
        for (WorldLayer * layer : worldLayers) {
            if (layer->getName() == name)
                return layer;
        }

        return nullptr;
    }

    WorldSceneGraph* World::getSceneGraph() {
        return &sceneGraph;
    }

    EventService& World::getEventService() {
        return localEventService;
    }
}