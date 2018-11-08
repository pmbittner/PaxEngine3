//
// Created by Paul on 28.05.2017.
//

#include <paxcore/world/World.h>

namespace PAX {
    World::World() {

    }

    World::~World() {
        for (std::pair<const std::string, WorldLayer*> entry : _layersByName) {
            delete entry.second;
        }
        _layersByName.clear();
    }

    void World::addLayer(WorldLayer *layer) {
        assert(_layersByName[layer->getName()] == nullptr);
        _layersByName[layer->getName()] = layer;
        _layers.push_back(layer);

        _sceneGraph.addChild(layer->getSceneGraph().get());
        layer->getEventService().setParent(&_localEventService);
    }

    void World::removeLayer(WorldLayer *layer) {
        _layersByName.erase(layer->getName());
        Util::removeFromVector(_layers, layer);

        _sceneGraph.removeChild(layer->getSceneGraph().get());
        layer->getEventService().setParent(nullptr);
    }

    const std::vector<WorldLayer*>& World::getLayers() {
        return _layers;
    }

    WorldLayer* World::getWorldLayerWithName(const std::string &name) {
        return _layersByName[name];
    }

    WorldSceneGraph* World::getSceneGraph() {
        return &_sceneGraph;
    }

    EventService& World::getEventService() {
        return _localEventService;
    }
}