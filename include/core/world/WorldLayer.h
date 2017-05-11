//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_WORLDLAYER_H
#define PAXENGINE3_WORLDLAYER_H

#include <string>
#include <vector>
#include <algorithm>
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

        std::unordered_map<std::type_index, void*> _componentAddedListeners;

        template<class EntityComponentType>
        void triggerEntityComponentAdded(EntityComponent *component) {
            std::type_index type = std::type_index(typeid(EntityComponentType));
            void* voidListeners = _componentAddedListeners[type];
            if (voidListeners) {
                EntityComponentAddedEvent<EntityComponentType> event(component, component->getOwner());
                std::vector<EventListener<EntityComponentAddedEvent<EntityComponentType>>*> *listeners = static_cast<std::vector<EventListener<EntityComponentAddedEvent<EntityComponentType>>*>*>(voidListeners);
                for (EventListener<EntityComponentAddedEvent<EntityComponentType>> *listener : *listeners)
                    listener->onEvent(&event);
            }
        }

    public:
        WorldLayer(std::string name = "WorldLayer", float z = 0);

        void spawn(Entity *entity);
        void despawn(Entity *entity);

        void addEntitySpawnedEventListener(EventListener<EntitySpawnedEvent> *listener);
        //void removeEntitySpawnedEventListener(EventListener<EntitySpawnedEvent> *listener);
        void addEntityDespawnedEventListener(EventListener<EntityDespawnedEvent> *listener);
        //void removeEntityDespawnedEventListener(EventListener<EntityDespawnedEvent> *listener);

        template<class EntityComponentType>
        void addEntityComponentAddedEventListener(EventListener<EntityComponentAddedEvent<EntityComponentType>> *listener) {
            std::type_index type = std::type_index(typeid(EntityComponentType));
            void* voidListeners = _componentAddedListeners[type];
            std::vector<EventListener<EntityComponentAddedEvent<EntityComponentType>>*> *listeners;

            if (!voidListeners) {
                listeners = new std::vector<EventListener<EntityComponentAddedEvent<EntityComponentType>>*>();
                _componentAddedListeners[type] = listeners;
            } else {
                listeners = static_cast<std::vector<EventListener<EntityComponentAddedEvent<EntityComponentType>>*>*>(voidListeners);
            }

            listeners->push_back(listener);
        }

        template<class EntityComponentType>
        void removeEntityComponentAddedEventListener(EventListener<EntitySpawnedEvent> *listener) {
            std::type_index type = std::type_index(typeid(EntityComponentType));
            void* voidListeners = _componentAddedListeners[type];

            if (voidListeners) {
                std::vector<EventListener<EntityComponentAddedEvent<EntityComponentType>>*> *listeners = static_cast<std::vector<EventListener<EntityComponentAddedEvent<EntityComponentType>>*>*>(voidListeners);
                auto index = std::find(listeners->begin(), listeners->end(), listener);
                if (index != listeners->end())
                    listeners->erase(index);
            }
        }

        //void addEntityComponentRemovedEventListener(EventListener<EntityDespawnedEvent> *listener);
        //void removeEntityComponentRemovedEventListener(EventListener<EntityDespawnedEvent> *listener);

        std::string getName();
    };
}

#endif //PAXENGINE3_WORLDLAYER_H
