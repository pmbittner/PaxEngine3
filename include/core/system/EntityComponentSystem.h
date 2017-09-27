//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_IGAMESYSTEM_H
#define PAXENGINE3_IGAMESYSTEM_H

#include <tuple>
#include <map>

#include "GameSystem.h"
#include "../Engine.h"
#include "../Game.h"
#include "../event/EventService.h"
#include "../world/event/EntitySpawnedEvent.h"
#include "../world/event/EntityDespawnedEvent.h"
#include "../world/event/ActiveWorldChangedEvent.h"

namespace PAX {
    template<typename... RequiredEntityComponents>
    class EntityComponentSystem : public GameSystem {
        std::map<World*, std::vector<Entity*>> _entities;
        World* _activeWorld;

        /* two functions are needed for unfolding the variadic template parameter RequiredEntityComponents */

        template<typename EntityComponent>
        void addListener(EventService &e) {
            e.add<EntityComponentAddedEvent<EntityComponent>, EntityComponentSystem, &EntityComponentSystem::onEntityAddEvent>(this);
            e.add<EntityComponentRemovedEvent<EntityComponent>, EntityComponentSystem, &EntityComponentSystem::onEntityComponentRemoved>(this);
        }

        template<typename EntityComponentType1, typename EntityComponentType2, typename... OtherEntityComponentTypes>
        void addListener(EventService &e) {
            addListener<EntityComponentType1>(e);
            addListener<EntityComponentType2, OtherEntityComponentTypes...>(e);
        }

        template<typename EntityComponent>
        void removeListener(EventService &e) {
            e.remove<EntityComponentAddedEvent<EntityComponent>, EntityComponentSystem, &EntityComponentSystem::onEntityAddEvent>(this);
            e.remove<EntityComponentRemovedEvent<EntityComponent>, EntityComponentSystem, &EntityComponentSystem::onEntityComponentRemoved>(this);
        }

        template<typename EntityComponentType1, typename EntityComponentType2, typename... OtherEntityComponentTypes>
        void removeListener(EventService &e) {
            removeListener<EntityComponentType1>(e);
            removeListener<EntityComponentType2, OtherEntityComponentTypes...>(e);
        }

    public:
        const std::vector<Entity*>& getEntities() {
            return _entities[_activeWorld];
        }

        bool isValid(Entity* e) {
            return e->has<RequiredEntityComponents...>();
        }

    private:
        void addWorld(World *world) {
            for (WorldLayer *layer : world->getLayers()) {
                for (Entity *e : layer->getEntities()) {
                    tryAdd(e);
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
                    e.remove<EntitySpawnedEvent, EntityComponentSystem, &EntityComponentSystem::onEntityAddEvent>(this);
                    e.remove<EntityDespawnedEvent, EntityComponentSystem, &EntityComponentSystem::onEntityDespawned>(this);
                    removeListener<RequiredEntityComponents...>(e);
                }

                _activeWorld = world;

                // Register listeners in/at new world
                if (_activeWorld) {
                    EventService &e = _activeWorld->getEventService();
                    e.add<EntitySpawnedEvent, EntityComponentSystem, &EntityComponentSystem::onEntityAddEvent>(this);
                    e.add<EntityDespawnedEvent, EntityComponentSystem, &EntityComponentSystem::onEntityDespawned>(this);
                    addListener<RequiredEntityComponents...>(e);
                }
            }
        }

        void add(Entity *entity) {
            if (_activeWorld)
                _entities[_activeWorld].push_back(entity);
        }

        void tryAdd(Entity *entity) {
            if (isValid(entity))
                add(entity);
        }

        void remove(Entity *entity) {
            if (_activeWorld)
                Util::removeFromVector(&_entities[_activeWorld], entity);
        }

    public:
        virtual void initialize(Game *game) override {
            game->ActiveWorldChanged.add<EntityComponentSystem, &EntityComponentSystem::onActiveWorldChanged>(this);
            game->WorldRegistered.add<EntityComponentSystem, &EntityComponentSystem::onWorldRegistered>(this);
            game->WorldUnregistered.add<EntityComponentSystem, &EntityComponentSystem::onWorldUnregistered>(this);

            for(World *world : game->getRegisteredWorlds())
                addWorld(world);

            setActiveWorld(game->getActiveWorld());
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

        template<typename Event>
        void onEntityAddEvent(Event &e) {
            tryAdd(e.entity);
        }

        void onEntityDespawned(EntityDespawnedEvent &e) {
            Entity *entity = e.entity;
            if (isValid(entity))
                remove(entity);
        }

        template<typename EntityComponentType>
        void onEntityComponentRemoved(EntityComponentRemovedEvent<EntityComponentType> &e) {
            Entity *entity = e.entity;
            if (!isValid(entity))
                remove(entity);
        }
    };
}

#endif //PAXENGINE3_IGAMESYSTEM_H
