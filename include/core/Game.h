//
// Created by Paul on 28.04.2017.
//

#ifndef PAXENGINE3_GAME_H
#define PAXENGINE3_GAME_H

#include <vector>

#include "EngineSystem.h"
#include "GameSystem.h"
#include "world/World.h"

namespace PAX {
    class Game : private EngineSystem {
    private:
        bool _initialized {false};
        std::vector<GameSystem*> _gameSystems;

        World *_activeWorld;

    public:
        virtual void initialize() override;
        virtual void update() override;

        World* getActiveWorld();
        void setActiveWorld(World *world);

        void addGameSystem(GameSystem *gameSystem);
        void removeGameSystem(GameSystem *gameSystem);
    };
}

#endif //PAXENGINE3_GAME_H
