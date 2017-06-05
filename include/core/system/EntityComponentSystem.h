//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_IGAMESYSTEM_H
#define PAXENGINE3_IGAMESYSTEM_H

#include <tuple>
#include "../Engine.h"
#include "EngineSystem.h"
#include "../event/EventService.h"
#include "../world/event/EntitySpawnedEvent.h"
#include "../world/event/EntityDespawnedEvent.h"

namespace PAX {
    template<typename... RequiredEntityComponents>
    class EntityComponentSystem : public EngineSystem {
        std::vector<Entity*> _entities;

        void add(Entity *entity) {
            _entities.push_back(entity);
        }

        void remove(Entity *entity) {
            Util::removeFromVector(&_entities, entity);
        }

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

    public:
        virtual void initialize() override {
            EventService &e = Engine::GetInstance()->getEventService();
            e.add<EntitySpawnedEvent, EntityComponentSystem, &EntityComponentSystem::onEntityAddEvent>(this);
            e.add<EntityDespawnedEvent, EntityComponentSystem, &EntityComponentSystem::onEntityDespawned>(this);

            addListener<RequiredEntityComponents...>(e);
        }

        template<typename Event>
        void onEntityAddEvent(Event &e) {
            Entity *entity = e.entity;
            if (isValid(entity))
                add(entity);
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

        const std::vector<Entity*> getEntities() {
            return _entities;
        }

        bool isValid(Entity* e) {
            return e->has<RequiredEntityComponents...>();
        }
    };
}

#endif //PAXENGINE3_IGAMESYSTEM_H
