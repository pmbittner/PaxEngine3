//
// Created by Paul on 15.08.2018.
//

#include <PaxEngineIncludes.h>

namespace PAX {
    int RayMarcher_main(int argc, char* argv[]);
}

int main(int argc, char* argv[]) {
    PAX::RayMarcher_main(argc, argv);
}

#include "raymarcher/Demo.h"
#include "raymarcher/Plugin.h"

// Plugin Includes
#include "paxsdl/SDLPlugin.h"
#include "paxsdl/opengl/SDLOpenGLPlugin.h"
#include "paxopengl/OpenGLPlugin.h"
//#include "paxphysics/Plugin.h"

int PAX::RayMarcher_main(int argc, char *argv[]) {
    int exitcode = 0;

    PAX::RayMarcher::Demo game;

    PAX::SDL::SDLPlugin                     sdl;
    PAX::OpenGL::OpenGLPlugin               openGL;
    PAX::SDL::OpenGL::SDLOpenGLPlugin       sdlOpenGLLink;
    PAX::RayMarcher::Plugin                 demoPlugin;

    PAX::Engine &engine = PAX::Engine::Instance();
    engine.initialize(
            &game,
            {
                    &sdl,
                    &openGL,
                    &sdlOpenGLLink,
                    &demoPlugin
            }
    );
    exitcode = engine.run();

    return exitcode;
}