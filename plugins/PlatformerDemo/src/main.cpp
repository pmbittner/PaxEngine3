//
// Created by Paul on 15.08.2018.
//

#include <MainIncludes.h>

namespace PAX {
    int PlatformerDemo_main(int argc, char* argv[]);
}

int main(int argc, char* argv[]) {
    PAX::PlatformerDemo_main(argc, argv);
}

#include <Demo.h>

// Plugin Includes
#include <sdl/include/SDLEnginePlugin.h>
#include <sdl/include/opengl/SDLOpenGLEnginePlugin.h>
#include <opengl/include/OpenGLEnginePlugin.h>
#include <physics/include/Plugin.h>
#include <PlatformerDemo/include/Plugin.h>

int PAX::PlatformerDemo_main(int argc, char *argv[]) {
    int exitcode = 0;

    PAX::PlatformerDemo::Demo game;

    PAX::SDL::SDLEnginePlugin               sdl;
    PAX::OpenGL::OpenGLEnginePlugin         openGL;
    PAX::SDL::OpenGL::SDLOpenGLEnginePlugin sdlOpenGLLink;
    PAX::Physics::Plugin                    physics;
    PAX::PlatformerDemo::Plugin             demoPlugin;

    PAX::Engine &engine = PAX::Engine::Instance();
    engine.initialize(
            &game,
            {
                    &sdl,
                    &openGL,
                    &sdlOpenGLLink,
                    &physics,
                    &demoPlugin
            }
    );
    exitcode = engine.run();

    return exitcode;
}