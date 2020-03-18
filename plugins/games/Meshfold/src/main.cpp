//
// Created by Paul on 15.08.2018.
//

#include <PaxEngineIncludes.h>

namespace PAX {
    int Meshfold_main(int argc, char* argv[]);
}

int main(int argc, char* argv[]) {
    PAX::Meshfold_main(argc, argv);
}

#include "meshfold/Meshfold.h"
#include "meshfold/Plugin.h"

// Plugin Includes
#include "paxsdl/SDLPlugin.h"
#include "paxsdl/opengl/SDLOpenGLPlugin.h"
#include "paxopengl/OpenGLPlugin.h"
//#include "paxphysics/Plugin.h"

int PAX::Meshfold_main(int argc, char *argv[]) {
    int exitcode = 0;

    PAX::Meshfold::Meshfold game;

    PAX::SDL::SDLPlugin                     sdl;
    PAX::OpenGL::OpenGLPlugin               openGL;
    PAX::SDL::OpenGL::SDLOpenGLPlugin       sdlOpenGLLink;
    PAX::Meshfold::Plugin                   meshfoldPlugin;

    PAX::Engine &engine = PAX::Engine::Instance();
    engine.initialize(
            &game,
            {
                    &sdl,
                    &openGL,
                    &sdlOpenGLLink,
                    &meshfoldPlugin
            }
    );
    exitcode = engine.run();

    return exitcode;
}