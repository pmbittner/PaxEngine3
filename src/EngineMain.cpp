//
// Created by Paul on 29.04.2017.
//

#include <test/ResourcesTest.h>
#include <test/trials/AllocatorConstructorTest.h>
#include <test/trials/InheritedTemplateTypeTest.h>
#include <test/EntityTest.h>
#include <demo/OpenGL/TerrainDemo.h>
#include <utility/reflection/TemplateTypeToString.h>
#include <demo/OpenGL/Platformer/PlatformerDemo.h>

#include "../include/EngineMain.h"

#include "../include/core/Engine.h"
#include "../include/sdl/SDLEngineSetup.h"

#include "../include/lib/easylogging++.h"
#include "../include/sdl/opengl/SDLOpenGLEngineSetup.h"

int PAX::Engine_Main(int argc, char *argv[]) {
    int exitcode = 0;

    EngineSetup *setup = new SDL::OpenGL::SDLOpenGLEngineSetup;
    Game *game = new Demo::PlatformerDemo();

    Engine &engine = Engine::Instance();
    engine.initialize(setup, game);
    /*
    PAX::TEST::ENTITY::test();
    //*/
    exitcode = engine.run();

    return exitcode;
}