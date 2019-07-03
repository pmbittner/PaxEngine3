//
// Created by Paul on 29.04.2017.
//

#include <algorithm>
#include <iostream>
#include <paxcore/Game.h>
#include <paxcore/Engine.h>
#include <paxcore/system/entity/BehaviourSystem.h>

namespace PAX {
    Game::Game() = default;
    Game::~Game() = default;

    void Game::initialize() {
        addSystem(std::make_unique<BehaviourSystem>());
        SystemManager::initialize();
    }

    void Game::terminate() {
        while (!_worlds.empty()) {
            World * world = *(_worlds.end() - 1);
            unregisterWorld(world, true);
            delete world;
        }

        SystemManager::terminate();
    }

    void Game::update() {
        SystemManager::update();
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
        if (world == _activeWorld) {
            if (force) {
                setActiveWorld(nullptr);
            } else {
                PAX_PRINT_WARN("Trying to unregister the active World " << world)
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
        return _activeWorld;
    }

    void Game::setActiveWorld(World *world) {
        if(world != nullptr && !isRegistered(world))
            registerWorld(world);

        World *oldActive = _activeWorld;

        if (oldActive)
            oldActive->getEventService().setParent(nullptr);

        _activeWorld = world;

        if (_activeWorld)
            _activeWorld->getEventService().setParent(&Services::GetEventService());

        ActiveWorldChangedEvent e(oldActive, _activeWorld);
        ActiveWorldChanged(e);
    }
}