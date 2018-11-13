//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_ENTITYCOMPONENTSYSTEM_H
#define PAXENGINE3_ENTITYCOMPONENTSYSTEM_H

#include <tuple>
#include <unordered_map>

#include <paxutil/event/EventService.h>

#include "GameSystem.h"
#include "../Engine.h"
#include "../Game.h"

#include "../world/event/EntitySpawnedEvent.h"
#include "../world/event/EntityDespawnedEvent.h"
#include "../world/event/ActiveWorldChangedEvent.h"

namespace PAX {
    template<typename... RequiredEntityComponents>
    class EntityComponentSystem : public GameSystem {
        std::unordered_map<World*, std::unordered_map<WorldLayer*, std::vector<Entity*>>> _entities;
        World* _activeWorld = nullptr;

        /* two functions are needed for unfolding the variadic template parameter RequiredEntityComponents */

        template<typename EntityComponent>
        void addEntityComponentListeners(EventService &e) {
            e.add<EntityComponentAddedEvent<EntityComponent>, EntityComponentSystem, &EntityComponentSystem::onEntityComponentsAdded>(this);
            e.add<EntityComponentRemovedEvent<EntityComponent>, EntityComponentSystem, &EntityComponentSystem::onEntityComponentRemoved>(this);
        }

        template<typename EntityComponentType1, typename EntityComponentType2, typename... OtherEntityComponentTypes>
        void addEntityComponentListeners(EventService &e) {
            addEntityComponentListeners<EntityComponentType1>(e);
            addEntityComponentListeners<EntityComponentType2, OtherEntityComponentTypes...>(e);
        }

        template<typename EntityComponent>
        void removeEntityComponentListeners(EventService &e) {
            e.remove<EntityComponentAddedEvent<EntityComponent>, EntityComponentSystem, &EntityComponentSystem::onEntityComponentsAdded>(this);
            e.remove<EntityComponentRemovedEvent<EntityComponent>, EntityComponentSystem, &EntityComponentSystem::onEntityComponentRemoved>(this);
        }

        template<typename EntityComponentType1, typename EntityComponentType2, typename... OtherEntityComponentTypes>
        void removeEntityComponentListeners(EventService &e) {
            removeEntityComponentListeners<EntityComponentType1>(e);
            removeEntityComponentListeners<EntityComponentType2, OtherEntityComponentTypes...>(e);
        }

    public:
        const std::unordered_map<WorldLayer*, std::vector<Entity*>>& getEntities() {
            return _entities[_activeWorld];
        }

        const std::vector<Entity*> & getEntities(WorldLayer * layer) {
            return _entities[_activeWorld][layer];
        }

        inline bool isValid(Entity* e) const {
            return e->has<RequiredEntityComponents...>();
        }

    private:
        void addWorld(World *world) {
            for (WorldLayer *layer : world->getLayers()) {
                for (Entity *e : layer->getEntities()) {
                    tryAdd(e, world);
                }
            }
        }

        void removeWorld(World *world) {
            _entities.erase(world);
        }

        void setActiveWorld(World *world) {
            if (_activeWorld != world) {
                // Remove listeners from old world
                if (_activeWorld) {
                    EventService &e = _activeWorld->getEventService();
                    e.remove<EntitySpawnedEvent, EntityComponentSystem, &EntityComponentSystem::onEntitySpawned>(this);
                    e.remove<EntityDespawnedEvent, EntityComponentSystem, &EntityComponentSystem::onEntityDespawned>(this);
                    removeEntityComponentListeners<RequiredEntityComponents...>(e);
                }

                _activeWorld = world;

                // Register listeners in/at new world
                if (_activeWorld) {
                    EventService &e = _activeWorld->getEventService();
                    e.add<EntitySpawnedEvent, EntityComponentSystem, &EntityComponentSystem::onEntitySpawned>(this);
                    e.add<EntityDespawnedEvent, EntityComponentSystem, &EntityComponentSystem::onEntityDespawned>(this);
                    addEntityComponentListeners<RequiredEntityComponents...>(e);
                }
            }
        }

        void add(Entity *entity, World *world) {
            if (world)
                _entities[world][entity->getWorldLayer()].push_back(entity);
        }

        void tryAdd(Entity *entity, World* world) {
            if (isValid(entity))
                add(entity, world);
        }

        bool remove(Entity *entity, World* world, WorldLayer* layer) {
            if (world) {
                return Util::removeFromVector(_entities[world][layer], entity);
            }

            return false;
        }

    public:
        virtual void initialize(Game *game) override {
            setActiveWorld(game->getActiveWorld());
            game->ActiveWorldChanged.add<EntityComponentSystem, &EntityComponentSystem::onActiveWorldChanged>(this);
            game->WorldRegistered.add<EntityComponentSystem, &EntityComponentSystem::onWorldRegistered>(this);
            game->WorldUnregistered.add<EntityComponentSystem, &EntityComponentSystem::onWorldUnregistered>(this);

            for(World *world : game->getRegisteredWorlds())
                addWorld(world);
        }

        virtual void terminate(Game * game) override {
            _entities.clear();
        }

        // EVENT LISTENERS /////////////////

        void onWorldRegistered(WorldEvent &event) {
            addWorld(event.world);
        }

        void onWorldUnregistered(WorldEvent &event) {
            removeWorld(event.world);
        }

        void onActiveWorldChanged(ActiveWorldChangedEvent &event) {
            setActiveWorld(event.newWorld);
        }

        void onEntitySpawned(EntitySpawnedEvent &e) {
            tryAdd(e.entity, _activeWorld);
        }

        template<typename EntityComponentType>
        void onEntityComponentsAdded(EntityComponentAddedEvent<EntityComponentType> &e) {
            tryAdd(e.entity, _activeWorld);
        }

        void onEntityDespawned(EntityDespawnedEvent &e) {
            Entity *entity = e.entity;
            if (isValid(entity))
                remove(entity, _activeWorld, e.oldWorldLayer);
        }

        template<typename EntityComponentType>
        void onEntityComponentRemoved(EntityComponentRemovedEvent<EntityComponentType> &e) {
            Entity *entity = e.entity;
            if (!isValid(entity))
                remove(entity, _activeWorld, e.entity->getWorldLayer());
        }
    };
}

#endif //PAXENGINE3_ENTITYCOMPONENTSYSTEM_H
