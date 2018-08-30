//
// Created by Paul on 17.04.2017.
//

#include <chrono>
#include <iostream>
#include <easylogging++.h>

#include <core/Engine.h>
#include <core/Game.h>
#include <core/EnginePlugin.h>
#include <core/generated/EngineInternalPlugin.h>

#include <utility/Sleep.h>
#include <core/time/Time.h>
#include <utility/io/CSVSettingsLoader.h>

namespace PAX {
    Engine *Engine::instance = nullptr;

    Engine::Engine() = default;

    Engine::~Engine() = default;

    bool Engine::initialize(Game *game, const std::vector<EnginePlugin*> &plugins) {
        LOG(INFO) << "[Engine::initialize] start";
        //PAX_assertNotNull(setup, "Engine::initialize: Setup not set! Abort initialization!");
        PAX_assertNotNull(game, "Engine::initialize: Game not set! Abort initialization!");

        Time::DeltaD = 1.0 / _targetUPS;
        Time::DeltaF = static_cast<float>(Time::DeltaD);

        _game = game;

        // Check if all dependencies of plugins are met
        for (const EnginePlugin* p : plugins) {
            p->checkDependencies(plugins);
        }

        _plugins.push_back(new EngineInternalPlugin());
        // Copy plugins
        _plugins.insert(std::end(_plugins), std::begin(plugins), std::end(plugins));

        LOG(INFO) << "[Engine::initialize] Plugins: initializing reflection data";
        for (EnginePlugin *plugin : _plugins) {
            plugin->internal_initializeReflectionData(Entity::entityComponentReflectionData);
        }

        LOG(INFO) << "[Engine::initialize] Plugins: initializing";
        for (EnginePlugin *plugin : _plugins) {
            plugin->initialize(*this);
        }

        LOG(INFO) << "[Engine::initialize] Plugins: registering Services";
        for (EnginePlugin *plugin : _plugins) {
            plugin->registerServices(_services);
        }

        LOG(INFO) << "[Engine::initialize] Plugins: registering ResourceLoaders";
        for (EnginePlugin *plugin : _plugins) {
            plugin->registerResourceLoaders(Services::GetResources());
        }

        LOG(INFO) << "[Engine::initialize] Plugins: registering Factories";
        for (EnginePlugin *plugin : _plugins) {
            plugin->registerFactories(Services::GetFactory());
        }

        LOG(INFO) << "[Engine::initialize] initialize Services";
        _services.initialize();

        LOG(INFO) << "[Engine::initialize] create Window";
        // load graphic settings
        Util::CSVSettingsLoader settings(Services::GetPaths().getRelativeResourcePath() + "config/initialWindow.paxconfig", '=', true);
        std::string title = settings["PaxEngine3_DefaultTitle"];
        int resX = settings.getInt("resolutionWidth");
        int resY = settings.getInt("resolutionHeight");

        _window = Services::GetFactory().create<Window>(title.c_str(), resX, resY);

        LOG(INFO) << "[Engine::initialize] initialize Renderer";
        _renderer.initialize();

        LOG(INFO) << "[Engine::initialize] Plugins: postInitialize";
        for (EnginePlugin *plugin : _plugins) {
            plugin->postInitialize(*this);
        }

        LOG(INFO) << "[Engine::initialize] initialize Game";
        _game->initialize();

        LOG(INFO) << "[Engine::initialize] done";
        return true;
    }


    int Engine::run() {
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
            timeLeft = (int) (1000 * timeTilNextRender.count());
            /*
            std::cout << "rt " << timeTilNextRender.count() << std::endl;
            std::cout << "ut " << timeTilNextUpdate.count() <<  " ... " << lag.count() << " / " << SPU.count() << std::endl;
            //*/
            if (timeLeft > 0) {
                PAX::ThreadSleep(timeLeft);
            }
        }
#undef DEF_NOW

        dispose();

        return 0;
    }


    void Engine::update() {
        _services.update();
        _game->update();
    }

    void Engine::render() {
        _renderer.render();
    }

    void Engine::stop() {
        _running = false;
    }

    Game *Engine::getGame() {
        return _game;
    }

    Window *Engine::getWindow() {
        return _window.get();
    }

    Renderer &Engine::getRenderer() {
        return _renderer;
    }

    double Engine::getFPS() {
        return _actualFPS;
    }

    Engine &Engine::Instance() {
        if (!instance)
            instance = new Engine();
        return *instance;
    }

    bool Engine::dispose() {
        //delete _game; // takes way too long :(
        return true;
    }
}