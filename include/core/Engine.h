//
// Created by Paul on 14.04.2017.
//

#ifndef PAXENGINE3_MAIN_H
#define PAXENGINE3_MAIN_H

#include "../core/rendering/Renderer.h"
#include "io/Window.h"
#include "EngineSetup.h"
#include "Services.h"

namespace PAX {
    class Game;

    class Engine {
    private:
        static Engine *instance;

        // GAME LOOP VARS ////////////////////////////////////////////////////////////
        bool _running {false};

        // constraint: _targetFPS <= _targetUPS
        double _targetFPS = 100;
        double _targetUPS = 100;

        double _actualFPS;
        double _actualUPS;

        // ARCHITECTURAL VARS ////////////////////////////////////////////////////////
        Services _services;
        Renderer _renderer;
        Game *_game = nullptr;

        Window *_window = nullptr;

        // FUNCTIONS /////////////////////////////////////////////////////////////////
        Engine();
        ~Engine();

        void update();
        void render();

    public:
        /// Takes ownership of game
        bool initialize(EngineSetup* setup, Game* game);
        int run();
        void stop();

        Window* getWindow();
        Game* getGame();
        Renderer& getRenderer();

        double getFPS();
        bool dispose();

        static Engine& Instance();
    };
}

#endif //PAXENGINE3_MAIN_H
