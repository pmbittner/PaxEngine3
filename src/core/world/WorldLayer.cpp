//
// Created by Paul on 08.05.2017.
//

#include <algorithm>
#include "../../../include/core/world/WorldLayer.h"
#include "../../../include/lib/easylogging++.h"
#include "../../../include/core/world/event/EntitySpawnedEvent.h"
#include "../../../include/core/Engine.h"

namespace PAX {
    WorldLayer::WorldLayer(std::string name, float z) : _name(name), _z(z) {

    }

    void WorldLayer::spawn(Entity *entity) {
        assert(entity->_worldLayer == nullptr);

        auto entityIter = std::find(_entities.begin(), _entities.end(), entity);
        if (entityIter == _entities.end()) {
            _entities.push_back(entity);
            entity->_worldLayer = this;
            EntitySpawnedEvent e(entity);
            //Engine::getInstance()->getEventService()->trigger(&e);
            for (EventListener<EntitySpawnedEvent>* listener : _spawnListeners)
                listener->onEvent(&e);
        }
    }

    void WorldLayer::despawn(Entity *entity) {
        auto entityIter = std::find(_entities.begin(), _entities.end(), entity);
        if (entityIter != _entities.end()) {
            _entities.erase(entityIter);
            EntityDespawnedEvent e(entity);
            //Engine::getInstance()->getEventService()->trigger(&e);
            for (EventListener<EntityDespawnedEvent>* listener : _despawnListeners)
                listener->onEvent(&e);
        }
    }

    std::string WorldLayer::getName() {
        return _name;
    }
}