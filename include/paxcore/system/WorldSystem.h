//
// Created by Paul on 24.03.2019.
//

#ifndef PAXENGINE3_WORLDSYSTEM_H
#define PAXENGINE3_WORLDSYSTEM_H

#include "GameSystem.h"

namespace PAX {
    class WorldSystem : public GameSystem {
    protected:
        World * activeWorld = nullptr;

        virtual void setActiveWorld(World * world);

    public:
        void initialize(Game *game) override;
        void terminate(Game * game) override;

        virtual void onWorldRegistered(WorldEvent &event) = 0;
        virtual void onWorldUnregistered(WorldEvent &event) = 0;

        void onActiveWorldChanged(ActiveWorldChangedEvent &event);
    };
}

#endif //PAXENGINE3_WORLDSYSTEM_H
