//
// Created by Paul Bittner on 17.03.2020.
//

#include <paxcore/Game.h>
#include <paxcore/system/GameSystem.h>

namespace PAX {
    GameSystem::~GameSystem() = default;

    void GameSystem::initialize(Game * game) {
        game->WorldAdded.add<GameSystem, &GameSystem::onWorldAdded>(this);
        game->WorldRemoved.add<GameSystem, &GameSystem::onWorldRemoved>(this);

        for(World *world : game->getWorlds()) {
            WorldEvent e(world);
            onWorldAdded(e);
        }
    }

    void GameSystem::terminate(Game *game) {
        for(World *world : game->getWorlds()) {
            WorldEvent e(world);
            onWorldRemoved(e);
        }

        game->WorldAdded.remove<GameSystem, &GameSystem::onWorldAdded>(this);
        game->WorldRemoved.remove<GameSystem, &GameSystem::onWorldRemoved>(this);
    }

    void GameSystem::setGame(PAX::Game *game) {
        this->game = game;
    }

    Game* GameSystem::getGame() {
        return this->game;
    }
}