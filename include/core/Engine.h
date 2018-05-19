//
// Created by Paul on 14.04.2017.
//

#ifndef PAXENGINE3_MAIN_H
#define PAXENGINE3_MAIN_H

#include <core/service/Services.h>
#include <core/io/Window.h>
#include <core/rendering/Renderer.h>

namespace PAX {
    class Game;
    class EnginePlugin;

    class Engine {
    private:
        static Engine *instance;

        // GAME LOOP VARS ////////////////////////////////////////////////////////////
        bool _running {false};

        // constraint: _targetFPS <= _targetUPS
        double _targetFPS = 60;
        double _targetUPS = 100;

        double _actualFPS;
        double _actualUPS;

        // ARCHITECTURAL VARS ////////////////////////////////////////////////////////
        Services _services;
        Renderer _renderer;
        Game *_game = nullptr;
        std::vector<EnginePlugin*> _plugins;

        std::shared_ptr<Window> _window = nullptr;

        // FUNCTIONS /////////////////////////////////////////////////////////////////
        Engine();
        ~Engine();

        void update();
        void render();

    public:
        /// Takes ownership of game
        bool initialize(Game* game, const std::vector<EnginePlugin*> &plugins);
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
