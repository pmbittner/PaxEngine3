//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_WORLDLAYER_H
#define PAXENGINE3_WORLDLAYER_H

#include <string>
#include <vector>
#include "WorldLayerLayout.h"
#include "../entity/Entity.h"
#include "../rendering/scenegraph/SceneGraph.h"
#include "event/EntitySpawnedEvent.h"
#include "../event/EventListener.h"
#include "event/EntityDespawnedEvent.h"

namespace PAX {
    class WorldLayer {
    private:
        std::string _name;
        WorldLayerLayout *_layout;
        float _z;

        SceneGraph _sceneGraph;
        SceneGraphBuilder _sceneGraphBuilder;

        std::vector<Entity*> _entities;

        std::vector<EventListener<EntitySpawnedEvent>*> _spawnListeners;
        std::vector<EventListener<EntityDespawnedEvent>*> _despawnListeners;

    public:
        WorldLayer(std::string name = "WorldLayer", float z = 0);

        void spawn(Entity *entity);
        void despawn(Entity *entity);

        std::string getName();
    };
}

#endif //PAXENGINE3_WORLDLAYER_H
