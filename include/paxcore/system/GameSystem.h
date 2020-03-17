//
// Created by bittner on 9/27/17.
//

#ifndef PAXENGINE3_GAMESYSTEM_H
#define PAXENGINE3_GAMESYSTEM_H

#include <paxcore/Game.h>
#include <polypropylene/system/System.h>

namespace PAX {
    class GameSystem : public System<Game>, public Updateable {

    };
}

#endif //PAXENGINE3_GAMESYSTEM_H
