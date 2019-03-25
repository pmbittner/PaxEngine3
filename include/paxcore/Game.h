//
// Created by Paul on 28.04.2017.
//

#ifndef PAXENGINE3_GAME_H
#define PAXENGINE3_GAME_H

#include <vector>
#include <paxutil/property/system/SystemManager.h>

#include "world/World.h"
#include "world/event/ActiveWorldChangedEvent.h"
#include "world/event/WorldEvent.h"

#include "system/EngineSystem.h"

namespace PAX {
    class BehaviourSystem;

    class Game : private EngineSystem, public SystemManager<Game>
    {
    private:
        std::vector<World*> _worlds;
        World *_activeWorld = nullptr;

    public:
        Game();
        ~Game() override;

        EventHandler<ActiveWorldChangedEvent&> ActiveWorldChanged;
        EventHandler<WorldEvent&> WorldRegistered;
        EventHandler<WorldEvent&> WorldUnregistered;

        void initialize() override;
        void terminate() override;
        void update() override;

        bool isRegistered(World *world);
        void registerWorld(World *world);
        bool unregisterWorld(World *world, bool force = false);
        const std::vector<World*>& getRegisteredWorlds();

        World* getActiveWorld();
        void setActiveWorld(World *world);
    };
}

#endif //PAXENGINE3_GAME_H
