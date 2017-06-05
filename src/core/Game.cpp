//
// Created by Paul on 29.04.2017.
//

#include <algorithm>
#include <iostream>
#include "../../include/core/Game.h"
#include "../../include/core/Engine.h"
#include "../../include/core/system/BehaviourSystem.h"

namespace PAX {
    void Game::initialize() {
        addSystem(new BehaviourSystem);

        for (EngineSystem *gameSystem : _systems)
            gameSystem->initialize();
        _initialized = true;
    }

    void Game::update() {
        for (EngineSystem *gameSystem : _systems)
            gameSystem->update();
    }

    World* Game::getActiveWorld() {
        return _activeWorld;
    }

    void Game::setActiveWorld(World *world) {
        assert(world);

        if (_activeWorld)
            _activeWorld->getEventService().setParent(nullptr);

        _activeWorld = world;
        _activeWorld->getEventService().setParent(&Engine::GetInstance()->getEventService());
    }

    void Game::addSystem(EngineSystem *system) {
        if (std::find(_systems.begin(), _systems.end(), system) == _systems.end()) {
            _systems.push_back(system);

            if (_initialized)
                system->initialize();
        }
    }

    void Game::removeSystem(EngineSystem *system) {
        Util::removeFromVector(&_systems, system);
    }
}