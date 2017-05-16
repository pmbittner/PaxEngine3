//
// Created by Paul on 17.04.2017.
//

#include <chrono>
#include <iostream>

#include "../../include/core/Engine.h"
#include "../../include/utility/Sleep.h"
#include "../../include/lib/easylogging++.h"

PAX::Engine *PAX::Engine::instance;

PAX::Engine::Engine() {
    instance = this;
}

PAX::Engine::~Engine() {
    instance = nullptr;
}

bool PAX::Engine::initialize(EngineSetup* setup) {
    LOG(INFO) << "Initializing engine";

    setup->initialize(this);

    _window = setup->createWindow();
    _window->create("PaxEngine3", 800, 600);

    _inputSystem = setup->createInputSystem();

    _inputSystem->initialize();
    _game.initialize();
    _renderer.initialize();
    return true;
}

//std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()).count();


int PAX::Engine::run() {
#define DEF_NOW std::chrono::high_resolution_clock::now()
    using namespace std::chrono;
    _running = true;

    _actualFPS = _targetFPS;
    _actualUPS = _targetUPS;

    /** LOOP VARS **/
    // Calculate how many seconds each frame should take for our target fps.
    // Think of this as slots, where in each one at least one frame/update
    // should be done.
    duration<double> SPF = duration<double>(1.0 / _targetFPS);
    duration<double> SPU = duration<double>(1.0 / _targetUPS);
    nanoseconds SPU_ns = duration_cast<nanoseconds>(SPU);

    high_resolution_clock::time_point loopStartTime;
    high_resolution_clock::time_point lastLoopStartTime = DEF_NOW;
    // time the last frame took.
    duration<double> dt(0);
    int timeLeft = 0;

    /** UPDATE VARS **/
    const long MAX_UPDATES = 1 << 4;

    // How long do all updates in one frame take together
    high_resolution_clock::time_point nextUpdateTime(lastLoopStartTime);
    // How many SPFs we are behind execution e.g. slower than desired.
    duration<double> lag(0);
    duration<double> update_duration;
    // num of updates each frame
    short updatesPerRender = 0;

    /** RENDER VARS **/
    high_resolution_clock::time_point renderStartTime(lastLoopStartTime);
    duration<double> render_duration;
    duration<double> timeTilNextRender(0);

    /** FPS & UPS COUNTER **/
    high_resolution_clock::time_point lastSecond(lastLoopStartTime);
    int frames = 0;
    int updates = 0;
    high_resolution_clock::time_point fpsUpsTimeStamp;

    while (_running) {
        // calculate delta time
        loopStartTime = DEF_NOW;
        dt = loopStartTime - lastLoopStartTime;
        lastLoopStartTime = loopStartTime;

        // UPDATE
        lag = loopStartTime - nextUpdateTime;
        updatesPerRender = 0;

        while (lag >= duration<double>::zero() && updatesPerRender < MAX_UPDATES) {
            update();
            nextUpdateTime += SPU_ns;
            lag -= SPU_ns;
            ++updatesPerRender;
        }

        // lag is to great to be catched up
        if (lag >= SPU_ns) {
            nextUpdateTime = loopStartTime - SPU_ns;
        }

        updates += updatesPerRender;
        update_duration = DEF_NOW - loopStartTime;

        // RENDER
        renderStartTime = DEF_NOW;
        render();
        ++frames;
        render_duration = DEF_NOW - renderStartTime;

        // count fps
        fpsUpsTimeStamp = DEF_NOW;
        if (fpsUpsTimeStamp >= lastSecond + seconds(1)) {
            duration<double> sPassed = fpsUpsTimeStamp - lastSecond;
            _actualFPS = frames / sPassed.count();
            _actualUPS = updates / sPassed.count();
            //std::cout << "FPS: " << _actualFPS << std::endl;
            //std::cout << "UPS: " << _actualUPS << std::endl;
            frames = 0;
            updates = 0;
            lastSecond = fpsUpsTimeStamp;
        }

        // Wait if your computer is faster than roadrunner to not kill it.
        timeTilNextRender = SPF - update_duration - render_duration;
        timeLeft = (int)(1000*timeTilNextRender.count());
        /*
        std::cout << "rt " << timeTilNextRender.count() << std::endl;
        std::cout << "ut " << timeTilNextUpdate.count() <<  " ... " << lag.count() << " / " << SPU.count() << std::endl;
        //*/
        if (timeLeft > 0) {
            PAX::ThreadSleep(timeLeft);
        }
    }
#undef DEF_NOW

    return 0;
}


void PAX::Engine::update() {
    //SDL_TEST_APPLICATION2::update();
    _inputSystem->update();
    _game.update();
}

void PAX::Engine::render() {
    //SDL_TEST_APPLICATION2::update();
    //SDL_TEST_APPLICATION2::render();
    _renderer.render();
}

void PAX::Engine::stop() {
    _running = false;
}

PAX::InputSystem* PAX::Engine::getInputSystem() {
    return _inputSystem;
}

PAX::Game* PAX::Engine::getGame() {
    return &_game;
}

PAX::Window* PAX::Engine::getWindow() {
    return _window;
}

PAX::EventService* PAX::Engine::getEventService() {
    return &_eventService;
}

double PAX::Engine::getFPS() {
    return _actualFPS;
}

PAX::Engine* PAX::Engine::getInstance() {
    if (instance)
        return instance;
    else
        return new Engine();
}

