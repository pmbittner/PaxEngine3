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
            worlds.push_back(world);
            world->getEventService().setParent(&getEventService());
            WorldEvent e(world);
            WorldAdded(e);
        }
    }

    bool Game::removeWorld(World *world) {
        if (Util::removeFromVector(worlds, world)) {
            WorldEvent e(world);
            WorldRemoved(e);
            world->getEventService().setParent(nullptr);
            return true;
        }

        return false;
    }

    const std::vector<World*>& Game::getWorlds() {
        return worlds;
    }

    void Game::update(UpdateOptions &options) {
        for (World * w : worlds) {
            options.activeWorld = w;

            for (auto &system : getSystems()) {
                system->update(options);
            }
        }

        options.activeWorld = nullptr;
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