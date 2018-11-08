//
// Created by Paul on 28.04.2017.
//

#ifndef PAXENGINE3_GAME_H
#define PAXENGINE3_GAME_H

#include <vector>

#include "world/World.h"
#include "world/event/ActiveWorldChangedEvent.h"
#include "world/event/WorldEvent.h"

#include "system/GameSystem.h"
#include "system/EngineSystem.h"

namespace PAX {
    class BehaviourSystem;

    class Game : private EngineSystem {
    private:
        bool _initialized {false};
        std::vector<GameSystem*> _systems;

        std::vector<World*> _worlds;
        World *_activeWorld = nullptr;

        // Default systems
        BehaviourSystem* _behaviourSystem = nullptr;

    public:
        Game();
        virtual ~Game();

        EventHandler<ActiveWorldChangedEvent&> ActiveWorldChanged;
        EventHandler<WorldEvent&> WorldRegistered;
        EventHandler<WorldEvent&> WorldUnregistered;

        virtual void initialize() override;
        virtual void terminate() override;
        virtual void update() override;

        bool isRegistered(World *world);
        void registerWorld(World *world);
        bool unregisterWorld(World *world);
        const std::vector<World*>& getRegisteredWorlds();

        World* getActiveWorld();
        void setActiveWorld(World *world);

        void addSystem(GameSystem *gameSystem);
        void removeSystem(GameSystem *gameSystem);
    };
}

#endif //PAXENGINE3_GAME_H
