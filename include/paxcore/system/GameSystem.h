//
// Created by bittner on 9/27/17.
//

#ifndef PAXENGINE3_GAMESYSTEM_H
#define PAXENGINE3_GAMESYSTEM_H

#include "paxcore/world/event/WorldEvent.h"

namespace PAX {
    class Game;

    class GameSystem : public Updateable {
        friend Game;
        Game * game = nullptr;

        void setGame(Game * game);

    public:
        GameSystem() = default;
        virtual ~GameSystem() = 0;

        virtual void initialize(Game*);
        virtual void terminate(Game*);

        Game * getGame();

        virtual void onWorldRegistered(WorldEvent &event) {};
        virtual void onWorldUnregistered(WorldEvent &event) {};
    };
}

#include "paxcore/Game.h"

#endif //PAXENGINE3_GAMESYSTEM_H
