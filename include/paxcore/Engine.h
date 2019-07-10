//
// Created by Paul on 14.04.2017.
//

#ifndef PAXENGINE3_MAIN_H
#define PAXENGINE3_MAIN_H

#include <paxcore/service/Services.h>
#include <paxcore/io/Window.h>
#include <paxcore/rendering/Renderer.h>

namespace PAX {
    class Game;
    class EnginePlugin;

    class Engine {
    private:
        static Engine *instance;

        // GAME LOOP VARS ////////////////////////////////////////////////////////////
        bool _running {false};

        //constraint: core_targetFPS <= core_targetUPS
        double _targetFPS = 60;
        double _targetUPS = 100;

        double _actualFPS = 0;
        double _actualUPS = 0;

        // ARCHITECTURAL VARS ////////////////////////////////////////////////////////
        Services _services;
        Renderer _renderer;
        Game *_game = nullptr;
        std::vector<EnginePlugin*> _plugins;

        // FUNCTIONS /////////////////////////////////////////////////////////////////
        Engine();
        ~Engine();

        void update();
        void render();

        bool terminate();

    public:
        /// Takes ownership of game
        bool initialize(Game* game, const std::vector<EnginePlugin*> &plugins);
        int run();
        void stop();

        Game* getGame();
        Renderer& getRenderer();

        double getFPS();
        double getUPS();

        static Engine& Instance();
    };
}

#endif //PAXENGINE3_MAIN_H
