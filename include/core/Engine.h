//
// Created by Paul on 14.04.2017.
//

#ifndef PAXENGINE3_MAIN_H
#define PAXENGINE3_MAIN_H

#include "io/InputSystem.h"
#include "Game.h"
#include "../core/rendering/Renderer.h"
#include "event/EventService.h"

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
        InputSystem* _inputSystem;
        Game _game;
        Renderer _renderer;
        std::vector<IEngineSystem*> _systems;

        Engine();
        void update();
        void render();

    public:
        ~Engine();

        bool initialize(InputSystem *inputSystem);
        int run();
        void stop();

        InputSystem* getInputSystem();
        Game* getGame();
        EventService* getEventService();

        double getFPS();

        static Engine* getInstance();
    };
}

#endif //PAXENGINE3_MAIN_H
