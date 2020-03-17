//
// Created by Paul on 24.03.2019.
//

#include <paxcore/system/WorldSystem.h>

namespace PAX {
    void WorldSystem::initialize(PAX::Game *game) {
        setActiveWorld(game->getActiveWorld());

        game->ActiveWorldChanged.add<WorldSystem, &WorldSystem::onActiveWorldChanged>(this);
        game->WorldRegistered.add<WorldSystem, &WorldSystem::onWorldRegistered>(this);
        game->WorldUnregistered.add<WorldSystem, &WorldSystem::onWorldUnregistered>(this);

        for(World *world : game->getRegisteredWorlds()) {
            WorldEvent e(world);
            onWorldRegistered(e);
        }
    }

    void WorldSystem::terminate(PAX::Game *game) {
        setActiveWorld(nullptr);

        for(World *world : game->getRegisteredWorlds()) {
            WorldEvent e(world);
            onWorldUnregistered(e);
        }

        game->ActiveWorldChanged.remove<WorldSystem, &WorldSystem::onActiveWorldChanged>(this);
        game->WorldRegistered.remove<WorldSystem, &WorldSystem::onWorldRegistered>(this);
        game->WorldUnregistered.remove<WorldSystem, &WorldSystem::onWorldUnregistered>(this);
    }

    void WorldSystem::setActiveWorld(PAX::World *world) {
        activeWorld = world;
    }

    void WorldSystem::onActiveWorldChanged(PAX::ActiveWorldChangedEvent &event) {
        setActiveWorld(event.newWorld);
    }

    World * WorldSystem::getActiveWorld() const {
        return activeWorld;
    }
}