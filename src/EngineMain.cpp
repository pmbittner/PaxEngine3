//
// Created by Paul on 29.04.2017.
//

#include "../include/EngineMain.h"

#include "../include/core/Engine.h"
#include "../include/sdl/SDLEngineSetup.h"
#include "../include/demo/DemoGame.h"

#include "../include/test/trials/GenericTypesInMapTest.h"
#include "../include/test/EntityTest.h"
#include "../include/test/trials/PrivateHackTest.h"
#include "../include/test/EventServiceTest.h"
#include "../include/test/trials/FriendTest.h"
#include "../include/test/trials/DelegateTest.h"
#include "../include/test/trials/StaticMember.h"
#include "../include/lib/easylogging++.h"
#include "../include/test/trials/SpecializedFunctionWithDifferentReturType.h"

int PAX::Engine_Main(int argc, char *argv[]) {
    int exitcode = 0;

    // FAMOUS TOGGLE COMMENT <3
    //*
    EngineSetup *setup = new SDLEngineSetup;
    Game *game = new Demo::DemoGame();

    Engine *engine = Engine::GetInstance();
    engine->initialize(setup, game);
    exitcode = engine->run();
    Engine::Dispose();
    /*/
    exitcode = PAX::TEST::ENTITY::test();// PAX::Test::SpecFuncDifRetType::run();
    LOG(INFO) << "Test finished with exit code " << exitcode;
    //*/

    return exitcode;
}