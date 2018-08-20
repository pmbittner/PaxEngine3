//
// Created by Paul on 15.08.2018.
//

#include <MainIncludes.h>

namespace PAX {
    int PlaygroundDemo_main(int argc, char* argv[]);
}

int main(int argc, char* argv[]) {
    PAX::PlaygroundDemo_main(argc, argv);
}

#include <Demo.h>
#include <core/Engine.h>

// Plugin Includes
#include <sdl/include/SDLEnginePlugin.h>
#include <sdl/include/opengl/SDLOpenGLEnginePlugin.h>
#include <opengl/include/OpenGLEnginePlugin.h>
#include <opengl/include/OpenGL2DEnginePlugin.h>
#include <PlaygroundDemo/include/Plugin.h>
#include <assimp/include/Plugin.h>

int PAX::PlaygroundDemo_main(int argc, char *argv[]) {
    int exitcode = 0;

    PAX::PlaygroundDemo::Demo game;

    PAX::SDL::SDLEnginePlugin               sdl;
    PAX::OpenGL::OpenGLEnginePlugin         openGL;
    PAX::OpenGL::OpenGL2DEnginePlugin       openGL2DFeatures;
    PAX::SDL::OpenGL::SDLOpenGLEnginePlugin sdlOpenGLLink;
    PAX::Assimp::Plugin                     modelLoader;
    PAX::PlaygroundDemo::Plugin             demoPlugin;

    PAX::Engine &engine = PAX::Engine::Instance();
    engine.initialize(
            &game,
            {
                    &sdl,
                    &openGL,
                    &openGL2DFeatures,
                    &sdlOpenGLLink,
                    &modelLoader,
                    &demoPlugin
            }
    );
    exitcode = engine.run();

    return exitcode;
}