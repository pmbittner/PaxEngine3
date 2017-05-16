//
// Created by Paul on 14.04.2017.
//

#ifndef PAXENGINE3_MAIN_H
#define PAXENGINE3_MAIN_H

#include "io/InputSystem.h"
#include "Game.h"
#include "../core/rendering/Renderer.h"
#include "event/EventService.h"
#include "io/Window.h"
#include "EngineSetup.h"

namespace PAX {
    class Engine {
    private:
        static Engine *instance;

        bool _running {false};

        // GAME LOOP VARS

        // constraint: _targetFPS < _targetUPS
        double _targetFPS = 100;
        double _targetUPS = 250;

        double _actualFPS;
        double _actualUPS;

        // ARCHITECTURAL VARS
        EventService _eventService;
        Game _game;
        Renderer _renderer;

        Window *_window;
        InputSystem* _inputSystem;
        std::vector<EngineSystem*> _systems;

        Engine();
        void update();
        void render();

    public:
        ~Engine();

        bool initialize(EngineSetup* setup);
        int run();
        void stop();

        InputSystem* getInputSystem();
        Game* getGame();
        Window* getWindow();
        EventService* getEventService();

        double getFPS();

        static Engine* getInstance();
    };
}

#endif //PAXENGINE3_MAIN_H
