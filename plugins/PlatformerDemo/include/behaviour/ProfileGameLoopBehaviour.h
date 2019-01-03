//
// Created by paul on 03.01.19.
//

#ifndef PAXENGINE3_PROFILEGAMELOOPBEHAVIOUR_H
#define PAXENGINE3_PROFILEGAMELOOPBEHAVIOUR_H

#include <paxcore/entity/component/Behaviour.h>
#include <paxcore/Engine.h>
#include <chrono>

namespace PAX {
    class ProfileGameLoopBehaviour : public Behaviour {
        PAX_PROPERTY_DERIVES(Behaviour)
        PAX_PROPERTY_IS_SINGLE

        std::chrono::high_resolution_clock::time_point StartTime;
        float secondsBetweenPrints = 3;

        void start() {
            StartTime = std::chrono::high_resolution_clock::now();
        }

        double time() {
            return std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - StartTime).count();
        }

    public:
        void attached(Entity& entity) override {
            start();
        }

        void update() override {
            if (time() > secondsBetweenPrints) {
                Engine &e = Engine::Instance();
                std::cout << "[ProfileGameLoopBehaviour::update] FPS = " << e.getFPS() << std::endl
                          << "[ProfileGameLoopBehaviour::update] UPS = " << e.getFPS() << std::endl << std::endl;
                start();
            }
        }
    };
}

#endif //PAXENGINE3_PROFILEGAMELOOPBEHAVIOUR_H
