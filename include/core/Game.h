//
// Created by Paul on 28.04.2017.
//

#ifndef PAXENGINE3_GAME_H
#define PAXENGINE3_GAME_H

#include <vector>

#include "system/EngineSystem.h"
#include "system/EntityComponentSystem.h"
#include "world/World.h"

namespace PAX {
    class Game : private EngineSystem {
    private:
        bool _initialized {false};
        std::vector<EngineSystem*> _systems;

        World *_activeWorld = nullptr;

    public:
        virtual void initialize() override;
        virtual void update() override;

        World* getActiveWorld();
        void setActiveWorld(World *world);

        void addSystem(EngineSystem *gameSystem);
        void removeSystem(EngineSystem *gameSystem);
    };
}

#endif //PAXENGINE3_GAME_H
