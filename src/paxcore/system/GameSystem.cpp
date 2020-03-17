//
// Created by Paul Bittner on 17.03.2020.
//

#include <paxcore/Game.h>
#include <paxcore/system/GameSystem.h>

namespace PAX {
    GameSystem::~GameSystem() = default;

    void GameSystem::initialize(Game * game) {
        game->WorldRegistered.add<GameSystem, &GameSystem::onWorldRegistered>(this);
        game->WorldUnregistered.add<GameSystem, &GameSystem::onWorldUnregistered>(this);

        for(World *world : game->getRegisteredWorlds()) {
            WorldEvent e(world);
            onWorldRegistered(e);
        }
    }

    void GameSystem::terminate(Game *game) {
        for(World *world : game->getRegisteredWorlds()) {
            WorldEvent e(world);
            onWorldUnregistered(e);
        }

        game->WorldRegistered.remove<GameSystem, &GameSystem::onWorldRegistered>(this);
        game->WorldUnregistered.remove<GameSystem, &GameSystem::onWorldUnregistered>(this);
    }

    void GameSystem::setGame(PAX::Game *game) {
        this->game = game;
    }

    Game* GameSystem::getGame() {
        return this->game;
    }
}