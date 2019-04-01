//
// Created by Paul on 15.08.2018.
//

#include <PaxEngineIncludes.h>

namespace PAX {
    int Tile_main(int argc, char* argv[]);
}

int main(int argc, char* argv[]) {
    PAX::Tile_main(argc, argv);
}

#include "tiledemo/Demo.h"
#include "tiledemo/Plugin.h"

// Plugin Includes
#include "paxsdl/SDLPlugin.h"
#include "paxsdl/opengl/SDLOpenGLPlugin.h"
#include "paxopengl/OpenGLEnginePlugin.h"
//#include "paxphysics/Plugin.h"
#include "paxtiles/Plugin.h"

int PAX::Tile_main(int argc, char *argv[]) {
    int exitcode = 0;

    PAX::TileDemo::Demo game;

    PAX::SDL::SDLPlugin                     sdl;
    PAX::OpenGL::OpenGLEnginePlugin         openGL;
    PAX::SDL::OpenGL::SDLOpenGLPlugin       sdlOpenGLLink;
    //PAX::Physics::Plugin                    physics;
    PAX::Tiles::Plugin                      tiles;
    PAX::TileDemo::Plugin                   demoPlugin;

    PAX::Engine &engine = PAX::Engine::Instance();
    engine.initialize(
            &game,
            {
                    &sdl,
                    &openGL,
                    &sdlOpenGLLink,
                    //&physics,
                    &tiles,
                    &demoPlugin
            }
    );
    exitcode = engine.run();

    return exitcode;
}