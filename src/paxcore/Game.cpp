//
// Created by Paul on 29.04.2017.
//

#include <algorithm>
#include <iostream>
#include <paxcore/Game.h>
#include <paxcore/Engine.h>
#include <paxcore/system/BehaviourSystem.h>

namespace PAX {
    Game::Game() {}
    Game::~Game() {}

    void Game::initialize() {
        assert(!_initialized);

        _behaviourSystem = new BehaviourSystem();
        addSystem(_behaviourSystem);

        for (GameSystem *gameSystem : _systems)
            gameSystem->initialize(this);

        _initialized = true;
    }

    void Game::terminate() {
        assert(_initialized);

        for (GameSystem *gameSystem : _systems)
            gameSystem->terminate(this);

        delete _behaviourSystem;
    }

    void Game::update() {
        for (GameSystem *gameSystem : _systems)
            gameSystem->update();
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

    bool Game::unregisterWorld(World *world) {
        if (world == _activeWorld) {
            LOG(WARNING) << "Trying to unregister the active World " << world;
            return false;
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
        assert(world);

        if(!isRegistered(world))
            registerWorld(world);

        World *oldActive = _activeWorld;

        if (_activeWorld)
            _activeWorld->getEventService().setParent(nullptr);

        _activeWorld = world;
        _activeWorld->getEventService().setParent(&Services::GetEventService());

        ActiveWorldChangedEvent e(oldActive, _activeWorld);
        ActiveWorldChanged(e);
    }

    void Game::addSystem(GameSystem *system) {
        if (std::find(_systems.begin(), _systems.end(), system) == _systems.end()) {
            _systems.push_back(system);

            if (_initialized)
                system->initialize(this);
        }
    }

    void Game::removeSystem(GameSystem *system) {
        if (Util::removeFromVector(_systems, system))
            system->terminate(this);
    }
}