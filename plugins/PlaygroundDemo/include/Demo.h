//
// Created by Paul on 06.01.2018.
//

#ifndef PAXENGINE3_PLAYGROUNDDEMO_H
#define PAXENGINE3_PLAYGROUNDDEMO_H

#include <core/Game.h>

namespace PAX {
    namespace PlaygroundDemo {
        class Demo : public Game {
            World *_world;
        public:
            Demo() : Game()
            {

            }

            ~Demo() override {

            }

            virtual void initialize() override {
                Game::initialize();

                LOG(INFO) << "Demo: initialize";

                _world = new World();
                setActiveWorld(_world);
            }
        };
    }
}

#endif //PAXENGINE3_PLAYGROUNDDEMO_H
