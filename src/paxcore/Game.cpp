//
// Created by Paul on 29.04.2017.
//

#include <algorithm>
#include <iostream>
#include <paxcore/Game.h>
#include <paxcore/Engine.h>
#include <paxcore/system/gameentity/BehaviourSystem.h>
#include <polypropylene/log/Assert.h>

namespace PAX {
    Game::Game() = default;
    Game::~Game() = default;

    void Game::initialize() {
        assert(!initialized);

        addSystem(std::make_unique<BehaviourSystem>());

        for (auto & system : systems) {
            system->initialize(this);
        }

        eventService.setParent(&Services::GetEventService());

        initialized = true;
    }

    void Game::terminate() {
        assert(initialized);

        while (!worlds.empty()) {
            World * world = *(worlds.end() - 1);
            removeWorld(world);
            PAX_ASSERT(pax_delete(world));
        }

        for (auto & system : systems) {
            system->terminate(this);
        }

        eventService.setParent(nullptr);
    }

    bool Game::hasWorld(World *world) {
        return Util::vectorContains(worlds, world);
    }

    void Game::addWorld(World *world) {
        if (!hasWorld(world)) {
            worldAddingQueue.push(world);
            if (!worldsLocked) {
                handleWorldAddingQueue();
            }
        }
    }

    void Game::handleWorldAddingQueue() {
        worldsLocked = true;
        while (!worldAddingQueue.empty()) {
            World * current = worldAddingQueue.front();
            worldAddingQueue.pop();
            worlds.push_back(current);
            current->getEventService().setParent(&getEventService());
            WorldEvent e(current);
            WorldAdded(e);
        }
        worldsLocked = false;
    }

    void Game::handleWorldRemovingQueue() {
        worldsLocked = true;
        while (!worldRemovingQueue.empty()) {
            World * current = worldRemovingQueue.front();
            worldRemovingQueue.pop();
            if (Util::removeFromVector(worlds, current)) {
                WorldEvent e(current);
                WorldRemoved(e);
                current->getEventService().setParent(nullptr);
            } else {
                PAX_THROW_RUNTIME_ERROR("Could not remove world from vector.");
            }
        }
        worldsLocked = false;
    }

    bool Game::removeWorld(World *world) {
        if (Util::vectorContains(worlds, world)) {
            worldRemovingQueue.push(world);
            if (!worldsLocked) {
                handleWorldRemovingQueue();
            }
            return true;
        }

        return false;
    }

    const std::vector<World*>& Game::getWorlds() {
        return worlds;
    }

    void Game::update(UpdateOptions &options) {
        worldsLocked = true;
        for (World * w : worlds) {
            options.activeWorld = w;

            for (auto &system : getSystems()) {
                system->update(options);
            }
        }
        options.activeWorld = nullptr;
        worldsLocked = false;

        handleWorldAddingQueue();
        handleWorldRemovingQueue();
    }

    EventService & Game::getEventService() {
        return eventService;
    }

    void Game::addSystem(std::unique_ptr<GameSystem>&& system) {
        if (initialized) {
            system->initialize(this);
        }
        system->setGame(this);
        systems.emplace_back(std::move(system));
    }

    const std::vector<std::unique_ptr<GameSystem>> & Game::getSystems() const {
        return systems;
    }
}