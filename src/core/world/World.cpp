//
// Created by Paul on 28.05.2017.
//

#include "../../../include/core/world/World.h"

namespace PAX {
    World::World() {
        _sceneGraph = new SceneGraph();
        addLayer(new WorldLayer(PAX_WORLDLAYERNAME_MAIN, 0));
        addLayer(new WorldLayer(PAX_WORLDLAYERNAME_GUI, 1));
    }

    World::~World() {
        for (std::pair<const std::string, WorldLayer*> entry : _layers) {
            delete entry.second;
        }
        _layers.clear();
    }

    void World::addLayer(WorldLayer *layer) {
        assert(_layers[layer->getName()] == nullptr);
        _layers[layer->getName()] = layer;

        _sceneGraph->addChild(layer->getSceneGraph());
        layer->getEventService().setParent(&_localEventService);
    }

    void World::removeLayer(WorldLayer *layer) {
        _layers.erase(layer->getName());

        _sceneGraph->removeChild(layer->getSceneGraph());
        layer->getEventService().setParent(nullptr);
    }

    WorldLayer* World::getWorldLayerWithName(const std::string &name) {
        return _layers[name];
    }

    WorldLayer* World::getMainLayer() {
        return getWorldLayerWithName(PAX_WORLDLAYERNAME_MAIN);
    }

    WorldLayer* World::getGUILayer() {
        return getWorldLayerWithName(PAX_WORLDLAYERNAME_GUI);
    }

    SceneGraph* World::getSceneGraph() {
        return _sceneGraph;
    }

    EventService& World::getEventService() {
        return _localEventService;
    }
}