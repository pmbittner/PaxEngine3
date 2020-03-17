//
// Created by Paul on 28.04.2017.
//

#ifndef PAXENGINE3_GAME_H
#define PAXENGINE3_GAME_H

#include <vector>

#include "system/GameSystem.h"

#include "world/World.h"
#include "world/event/ActiveWorldChangedEvent.h"
#include "world/event/WorldEvent.h"

namespace PAX {
    class BehaviourSystem;

    class Game : public Updateable
    {
    private:
        bool initialized = false;
        EventService eventService;
        std::set<std::unique_ptr<GameSystem>> systems;
        std::vector<World*> _worlds;
        World * activeWorld = nullptr;

    public:
        Game();
        ~Game() override;

        EventHandler<ActiveWorldChangedEvent&> ActiveWorldChanged;
        EventHandler<WorldEvent&> WorldRegistered;
        EventHandler<WorldEvent&> WorldUnregistered;

        virtual void initialize();
        virtual void terminate();

        bool isRegistered(World *world);
        void registerWorld(World *world);
        bool unregisterWorld(World *world, bool force = false);
        const std::vector<World*>& getRegisteredWorlds();

        World* getActiveWorld();
        void setActiveWorld(World *world);

        void update(UpdateOptions & options) override;

        EventService & getEventService();

        /**
         * Takes ownership if the given system.
         * @param system
         */
        void addSystem(std::unique_ptr<GameSystem> system);

        PAX_NODISCARD const std::set<std::unique_ptr<GameSystem>> & getSystems() const;

        template<class T>
        T * getSystem() const {
            for (const std::unique_ptr<GameSystem> & s : systems) {
                if (auto t = dynamic_cast<T*>(s.get())) {
                    return t;
                }
            }

            return nullptr;
        }
    };
}

#endif //PAXENGINE3_GAME_H
