//
// Created by Paul on 15.08.2018.
//

#include <PaxEngineIncludes.h>

namespace PAX {
    int PlatformerDemo_main(int argc, char* argv[]);
}

int main(int argc, char* argv[]) {
    PAX::PlatformerDemo_main(argc, argv);
}

#include "platformerdemo/Demo.h"
#include "platformerdemo/Plugin.h"

// Plugin Includes
#include "paxsdl/SDLPlugin.h"
#include "paxsdl/opengl/SDLOpenGLPlugin.h"
#include "paxphysics/Plugin.h"
#include "paxtiles/Plugin.h"

int PAX::PlatformerDemo_main(int argc, char *argv[]) {
    int exitcode = 0;

    PAX::PlatformerDemo::Demo game;

    PAX::SDL::SDLPlugin                     sdl;
    PAX::OpenGL::OpenGLPlugin               openGL;
    PAX::SDL::OpenGL::SDLOpenGLPlugin       sdlOpenGLLink;
    PAX::Physics::Plugin                    physics;
    PAX::Tiles::Plugin                      tiles;
    PAX::PlatformerDemo::Plugin             demoPlugin;

    PAX::Engine &engine = PAX::Engine::Instance();
    engine.initialize(
            &game,
            {
                    &sdl,
                    &openGL,
                    &sdlOpenGLLink,
                    &physics,
                    &tiles,
                    &demoPlugin
            }
    );
    exitcode = engine.run();

    return exitcode;
}