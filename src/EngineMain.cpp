//
// Created by Paul on 29.04.2017.
//

#include <test/ResourcesTest.h>
#include <test/trials/AllocatorConstructorTest.h>
#include <test/trials/InheritedTemplateTypeTest.h>
#include <test/EntityTest.h>

#include "../include/EngineMain.h"

#include "../include/core/Engine.h"
#include "../include/sdl/SDLEngineSetup.h"
#include "../include/demo/SDLDemo.h"

#include "../include/lib/easylogging++.h"
#include "../include/sdl/opengl/SDLOpenGLEngineSetup.h"
#include "../include/demo/OpenGL/PadiDemo.h"
#include "../include/demo/OpenGL/RenderTests.h"

int PAX::Engine_Main(int argc, char *argv[]) {
    //*
    PAX::TEST::ENTITY::test();
    //*/

    int exitcode = 0;

    EngineSetup *setup = new SDL::OpenGL::SDLOpenGLEngineSetup;
    Game *game = new Demo::RenderTests();

    Engine &engine = Engine::Instance();
    engine.initialize(setup, game);
    exitcode = engine.run();

    return exitcode;
}