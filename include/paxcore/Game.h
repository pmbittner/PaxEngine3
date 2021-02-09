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
        std::vector<std::unique_ptr<GameSystem>> systems;
        std::vector<World*> worlds;

    public:
        Game();
        ~Game() override;

        EventHandler<WorldEvent&> WorldAdded;
        EventHandler<WorldEvent&> WorldRemoved;

        virtual void initialize();
        virtual void terminate();

        bool hasWorld(World *world);
        void addWorld(World *world);
        bool removeWorld(World *world);
        const std::vector<World*>& getWorlds();

        void update(UpdateOptions & options) override;

        EventService & getEventService();

        /**
         * Takes ownership of the given system.
         * @param system
         */
        void addSystem(std::unique_ptr<GameSystem>&& system);

        PAX_NODISCARD const std::vector<std::unique_ptr<GameSystem>> & getSystems() const;

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
