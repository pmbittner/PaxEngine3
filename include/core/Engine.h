//
// Created by Paul on 14.04.2017.
//

#ifndef PAXENGINE3_MAIN_H
#define PAXENGINE3_MAIN_H

#include "io/InputSystem.h"
#include "../core/rendering/Renderer.h"
#include "event/EventService.h"
#include "io/Window.h"
#include "EngineSetup.h"

namespace PAX {
    class Game;

    class Engine {
    private:
        static Engine *instance;

        // GAME LOOP VARS ////////////////////////////////////////////////////////////
        bool _running {false};

        // constraint: _targetFPS <= _targetUPS
        double _targetFPS = 250;
        double _targetUPS = 250;

        double _actualFPS;
        double _actualUPS;

        // ARCHITECTURAL VARS ////////////////////////////////////////////////////////
        EventService _eventService;
        Renderer _renderer;

        Game *_game = nullptr;
        Window *_window = nullptr;
        InputSystem* _inputSystem = nullptr;

        // FUNCTIONS /////////////////////////////////////////////////////////////////
        Engine();
        ~Engine();

        void update();
        void render();

    public:
        bool initialize(EngineSetup* setup, Game* game);
        int run();
        void stop();

        InputSystem* getInputSystem();
        Window* getWindow();
        Game* getGame();
        EventService& getEventService();
        Renderer& getRenderer();

        double getFPS();

        static Engine* GetInstance();
        static bool Dispose();
    };
}

#endif //PAXENGINE3_MAIN_H
