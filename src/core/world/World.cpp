//
// Created by Paul on 28.05.2017.
//

#include "../../../include/core/world/World.h"

namespace PAX {
    World::World() {
        addLayer(new WorldLayer(PAX_WORLDLAYERNAME_MAIN, 0));
        addLayer(new WorldLayer(PAX_WORLDLAYERNAME_GUI, 1));
    }

    World::~World() {
        for (std::pair<std::string, WorldLayer*> entry : _layers) {
            delete entry.second;
        }
        _layers.clear();
    }

    void World::addLayer(WorldLayer *layer) {
        assert(_layers[layer->getName()] == nullptr);
        _layers[layer->getName()] = layer;
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
}