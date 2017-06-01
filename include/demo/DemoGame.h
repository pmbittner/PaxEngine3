//
// Created by paul on 01.06.17.
//

#ifndef PAXENGINE3_DEMOGAME_H
#define PAXENGINE3_DEMOGAME_H

#include "../core/Game.h"
#include "../test/SDLTestApplication2.h"

namespace PAX {
    namespace Demo {
        class DemoGame : public Game {
        public:
            virtual void initialize() override {
                Game::initialize();
                addGameSystem(new SDL_TEST_APPLICATION2::SDLTestApplication2GameSystem);
            }
        };
    }
}

#endif //PAXENGINE3_DEMOGAME_H
