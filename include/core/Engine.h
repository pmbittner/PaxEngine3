//
// Created by Paul on 14.04.2017.
//

#ifndef PAXENGINE3_MAIN_H
#define PAXENGINE3_MAIN_H

#include "InputSystem.h"
#include "Game.h"
#include "../core/rendering/Renderer.h"

namespace PAX {
    class Engine {
    private:
        static Engine *instance;

        bool _running {false};

        // GAME LOOP VARS

        // constraint: _targetFPS < _targetUPS
        double _targetFPS = 100;//bei Double.POSITIVE_INFINITY spackt die GUI ab
        double _targetUPS = 250;

        double _actualFPS;
        double _actualUPS;

        // ARCHITECTURAL VARS
        InputSystem _inputSystem;
        Game _game;
        Renderer _renderer;
        std::vector<IEngineSystem*> _systems;

        Engine();
        void update();
        void render();

    public:
        ~Engine();

        bool initialize();
        int run();
        void stop();

        InputSystem* getInputSystem();
        Game* getGame();

        double getFPS();

        static Engine* getInstance();
    };
}

#endif //PAXENGINE3_MAIN_H
