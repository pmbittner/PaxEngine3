//
// Created by Paul on 28.05.2017.
//

#include <paxcore/world/World.h>
#include <paxcore/Engine.h>
#include <paxcore/Game.h>

namespace PAX {
    World::World() : worldLayers(localEventService) {

    }

    World::~World() {
        while (!worldLayers.empty()) {
            WorldLayer * layer = *worldLayers.getPropertyContainers().begin();
            removeLayer(layer);
            delete layer;
        }
    }

    void World::setActive(bool active) {
        this->active = active;

        for (WorldLayer * wl : worldLayers) {
            wl->worldActivityChanged(active);
        }
    }

    bool World::isActive() const {
        return active;
    }

    void World::addLayer(WorldLayer *layer) {
        if (worldLayers.add(layer)) {
            sceneGraph.addChild(layer->getSceneGraph().get());
            layer->getEventService().setParent(&localEventService);
            layer->setWorld(this);

            WorldLayerAddedEvent e(this, layer);
            localEventService(e);
        }
    }

    void World::removeLayer(WorldLayer *layer) {
        if (worldLayers.remove(layer)) {
            sceneGraph.removeChild(layer->getSceneGraph().get());
            layer->getEventService().setParent(nullptr);
            layer->setWorld(nullptr);

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