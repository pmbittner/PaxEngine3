//
// Created by Paul on 29.04.2017.
//

#include <easylogging++.h>
#include <EngineMain.h>


int PAX::Engine_Main(int argc, char *argv[]) {
    int exitcode = 0;

    Platformer::PlatformerDemo game;

    PAX::SDL::SDLEnginePlugin               sdl;
    PAX::OpenGL::OpenGLEnginePlugin         openGL;
    PAX::OpenGL::OpenGL2DEnginePlugin       openGL2DFeatures;
    PAX::SDL::OpenGL::SDLOpenGLEnginePlugin sdlOpenGLLink;
    PAX::Physics::Plugin                    physics;

    Engine &engine = Engine::Instance();
    engine.initialize(
            &game,
            {
                    &sdl,
                    &openGL,
                    &openGL2DFeatures,
                    &sdlOpenGLLink,
                    &physics
            }
    );
    exitcode = engine.run();

    return exitcode;
}