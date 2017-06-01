//
// Created by Paul on 29.04.2017.
//

#include <algorithm>
#include <iostream>
#include "../../include/core/Game.h"
#include "../../include/core/Engine.h"

namespace PAX {
    void Game::initialize() {
        for (GameSystem *gameSystem : _gameSystems)
            gameSystem->initialize();
        _initialized = true;
    }

    void Game::update() {
        for (GameSystem *gameSystem : _gameSystems)
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

    void Game::addGameSystem(GameSystem *gameSystem) {
        if (std::find(_gameSystems.begin(), _gameSystems.end(), gameSystem) == _gameSystems.end()) {
            _gameSystems.push_back(gameSystem);

            if (_initialized)
                gameSystem->initialize();
        }
    }

    void Game::removeGameSystem(GameSystem *gameSystem) {
        auto gameSystemIterator = std::find(_gameSystems.begin(), _gameSystems.end(), gameSystem);
        if (gameSystemIterator != _gameSystems.end())
            _gameSystems.erase(gameSystemIterator);
    }
}