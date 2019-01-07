//
// Created by Paul on 15.08.2018.
//

#include <PaxEngineIncludes.h>

namespace PAX {
    int PlaygroundDemo_main(int argc, char* argv[]);
}

int main(int argc, char* argv[]) {
    PAX::PlaygroundDemo_main(argc, argv);
}

#include <Demo.h>

// Plugin Includes
#include <paxsdl/include/SDLPlugin.h>
#include <paxsdl/include/opengl/SDLOpenGLPlugin.h>
#include <paxopengl/include/OpenGLEnginePlugin.h>
#include <paxassetimport/include/Plugin.h>
#include <PlaygroundDemo/include/Plugin.h>

int PAX::PlaygroundDemo_main(int argc, char *argv[]) {
    int exitcode = 0;

    PAX::PlaygroundDemo::Demo game;

    PAX::SDL::SDLPlugin               sdl;
    PAX::OpenGL::OpenGLEnginePlugin         openGL;
    PAX::SDL::OpenGL::SDLOpenGLPlugin sdlOpenGLLink;
    PAX::AssetImport::Plugin                modelLoader;
    PAX::PlaygroundDemo::Plugin             demoPlugin;

    PAX::Engine &engine = PAX::Engine::Instance();
    engine.initialize(
            &game,
            {
                    &sdl,
                    &openGL,
                    &sdlOpenGLLink,
                    &modelLoader,
                    &demoPlugin
            }
    );
    exitcode = engine.run();

    return exitcode;
}