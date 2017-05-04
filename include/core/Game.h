//
// Created by Paul on 28.04.2017.
//

#ifndef PAXENGINE3_GAME_H
#define PAXENGINE3_GAME_H

#include <vector>

#include "interfaces/IEngineSystem.h"
#include "interfaces/IGameSystem.h"

namespace PAX {
    class Game : private IEngineSystem {
    private:
        bool _initialized {false};
        std::vector<IGameSystem*> _gameSystems;

    public:
        virtual void initialize() override;
        virtual void update() override;

        void addGameSystem(IGameSystem *gameSystem);
        void removeGameSystem(IGameSystem *gameSystem);
    };
}

#endif //PAXENGINE3_GAME_H
