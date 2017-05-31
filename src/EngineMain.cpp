//
// Created by Paul on 29.04.2017.
//

#include "../include/EngineMain.h"

#include "../include/core/Engine.h"
#include "../include/test/SDLTestApplication2.h"
#include "../include/test/trials/GenericTypesInMapTest.h"
#include "../include/test/EntityTest.h"
#include "../include/lib/easylogging++.h"
#include "../include/test/trials/PrivateHackTest.h"
#include "../include/test/EventServiceTest.h"
#include "../include/sdl/SDLInputSystem.h"
#include "../include/sdl/SDLWindow.h"
#include "../include/sdl/SDLEngineSetup.h"

#include "../include/test/trials/FriendTest.h"
#include "../include/test/trials/DelegateTest.h"

int PAX::Engine_Main(int argc, char *argv[]) {
    int exitcode = 0;

    EngineSetup *setup = new SDLEngineSetup;
    GameSystem *testGameSystem = new SDL_TEST_APPLICATION2::SDLTestApplication2GameSystem;

    Engine *engine = Engine::getInstance();
    engine->getGame().addGameSystem(testGameSystem);

    // FAMOUS TOGGLE COMMENT <3
    //*
    engine->initialize(setup);

    exitcode = engine->run();
    /*/
    exitcode = PAX::Test::Event::run();
    LOG(INFO) << "Test finished with exit code " << exitcode;
    //*/

    delete engine;

    return exitcode;
}