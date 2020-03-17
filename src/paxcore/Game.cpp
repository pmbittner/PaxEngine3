//
// Created by Paul on 29.04.2017.
//

#include <algorithm>
#include <iostream>
#include <paxcore/Game.h>
#include <paxcore/Engine.h>
#include <paxcore/system/gameentity/BehaviourSystem.h>

namespace PAX {
    Game::Game() = default;
    Game::~Game() = default;

    void Game::initialize() {
        assert(!initialized);

        addSystem(std::make_unique<BehaviourSystem>());

        for (auto & system : systems) {
            system->initialize(this);
        }

        initialized = true;
    }

    void Game::terminate() {
        assert(initialized);

        while (!_worlds.empty()) {
            World * world = *(_worlds.end() - 1);
            unregisterWorld(world, true);
            delete world;
        }

        for (auto & system : systems) {
            system->terminate(this);
        }
    }

    bool Game::isRegistered(World *world) {
        return Util::vectorContains(_worlds, world);
    }

    void Game::registerWorld(World *world) {
        if (!isRegistered(world)) {
            _worlds.push_back(world);
            WorldEvent e(world);
            WorldRegistered(e);
        }
    }

    bool Game::unregisterWorld(World *world, bool force) {
        if (world == activeWorld) {
            if (force) {
                setActiveWorld(nullptr);
            } else {
                PAX_LOG(Log::Level::Warn, "Trying to unregister the active World " << world);
                return false;
            }
        }

        if (Util::removeFromVector(_worlds, world)) {
            WorldEvent e(world);
            WorldUnregistered(e);

            return true;
        }

        return false;
    }

    const std::vector<World*>& Game::getRegisteredWorlds() {
        return _worlds;
    }

    World* Game::getActiveWorld() {
        return activeWorld;
    }

    void Game::setActiveWorld(World *world) {
        if(world != nullptr && !isRegistered(world))
            registerWorld(world);

        World *oldActive = activeWorld;

        if (oldActive) {
            oldActive->getEventService().setParent(nullptr);
        }

        activeWorld = world;

        if (activeWorld) {
            activeWorld->getEventService().setParent(&Services::GetEventService());
        }

        ActiveWorldChangedEvent e(oldActive, activeWorld);
        ActiveWorldChanged(e);
    }

    void Game::update(UpdateOptions &options) {
        for (auto &system : getSystems()) {
            system->update(options);
        }
    }

    EventService & Game::getEventService() {
        return eventService;
    }

    void Game::addSystem(std::unique_ptr<GameSystem> system) {
        if (initialized)
            system->initialize(this);
        system->setGame(this);
        systems.insert(std::move(system));
    }

    const std::set<std::unique_ptr<GameSystem>> & Game::getSystems() const {
        return systems;
    }
}