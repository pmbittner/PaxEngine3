//
// Created by bittner on 9/27/17.
//

#ifndef PAXENGINE3_GAMESYSTEM_H
#define PAXENGINE3_GAMESYSTEM_H

#include "System.h"

namespace PAX {
    class Game;

    class GameSystem : public System {
    public:
        virtual void initialize(Game *game) = 0;
        virtual void terminate(Game * game) = 0;
    };
}

#endif //PAXENGINE3_GAMESYSTEM_H
