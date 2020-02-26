//
// Created by Paul on 28.04.2017.
//

#ifndef PAXENGINE3_GAME_H
#define PAXENGINE3_GAME_H

#include <vector>
#include "polypropylene/system/SystemManager.h"

#include "world/World.h"
#include "world/event/ActiveWorldChangedEvent.h"
#include "world/event/WorldEvent.h"

namespace PAX {
    class BehaviourSystem;

    class Game : public SystemManager<Game>, public Updateable
    {
    private:
        std::vector<World*> _worlds;
        World *_activeWorld = nullptr;
        EventService eventService;

    public:
        Game();
        ~Game() override;

        EventHandler<ActiveWorldChangedEvent&> ActiveWorldChanged;
        EventHandler<WorldEvent&> WorldRegistered;
        EventHandler<WorldEvent&> WorldUnregistered;

        void initialize() override;
        void terminate() override;

        bool isRegistered(World *world);
        void registerWorld(World *world);
        bool unregisterWorld(World *world, bool force = false);
        const std::vector<World*>& getRegisteredWorlds();

        World* getActiveWorld();
        void setActiveWorld(World *world);

        void update(UpdateOptions & options) override;

        EventService & getEventService();
    };
}

#endif //PAXENGINE3_GAME_H
