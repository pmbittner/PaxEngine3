//
// Created by Paul on 28.04.2017.
//

#ifndef PAXENGINE3_GAME_H
#define PAXENGINE3_GAME_H

#include <vector>

#include "system/GameSystem.h"
#include "system/EngineSystem.h"
#include "world/World.h"
#include "world/event/ActiveWorldChangedEvent.h"
#include "world/event/WorldEvent.h"

namespace PAX {
    class Game : private EngineSystem {
    private:
        bool _initialized {false};
        std::vector<GameSystem*> _systems;

        std::vector<World*> _worlds;
        World *_activeWorld = nullptr;

    public:
        EventHandler<ActiveWorldChangedEvent&> ActiveWorldChanged;
        EventHandler<WorldEvent&> WorldRegistered;
        EventHandler<WorldEvent&> WorldUnregistered;

        virtual void initialize() override;
        virtual void update() override;

        bool isRegistered(World *world);
        void registerWorld(World *world);
        void unregisterWorld(World *world);
        const std::vector<World*>& getRegisteredWorlds();

        World* getActiveWorld();
        void setActiveWorld(World *world);

        void addSystem(GameSystem *gameSystem);
        void removeSystem(GameSystem *gameSystem);
    };
}

#endif //PAXENGINE3_GAME_H
