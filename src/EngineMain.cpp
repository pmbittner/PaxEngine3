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


int PAX::Engine_Main(int argc, char *argv[]) {
    int exitcode = 0;
    // FAMOUS TOGGLE COMMENT <3

    EngineSetup *setup = new SDLEngineSetup;

    Engine *engine = Engine::getInstance();

    IGameSystem *testGameSystem = new SDL_TEST_APPLICATION2::SDLTestApplication2GameSystem;
    engine->getGame()->addGameSystem(testGameSystem);

    engine->initialize(setup);

    exitcode = engine->run();
    delete engine;
    /*/
    exitcode = PAX::TEST::eventServiceText();
    LOG(INFO) << "Test finished with exit code " << exitcode;
    //*/

    return exitcode;
}