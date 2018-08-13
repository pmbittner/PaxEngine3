//
// Created by Paul on 29.04.2017.
//

#include <easylogging++.h>

#include <demo/Platformer/PlatformerDemo.h>

#include <EngineMain.h>

#include <sdl/include/SDLEnginePlugin.h>
#include <sdl/include/opengl/SDLOpenGLEnginePlugin.h>
#include <opengl/include/OpenGLEnginePlugin.h>
#include <opengl/include/OpenGL2DEnginePlugin.h>

int PAX::Engine_Main(int argc, char *argv[]) {
    int exitcode = 0;

    Platformer::PlatformerDemo game;

    PAX::SDL::SDLEnginePlugin               sdl;
    PAX::OpenGL::OpenGLEnginePlugin         openGL;
    PAX::OpenGL::OpenGL2DEnginePlugin       openGL2DFeatures;
    PAX::SDL::OpenGL::SDLOpenGLEnginePlugin sdlOpenGLLink;

    Engine &engine = Engine::Instance();
    engine.initialize(
            &game,
            {
                    &sdl,
                    &openGL,
                    &openGL2DFeatures,
                    &sdlOpenGLLink
            }
    );
    exitcode = engine.run();

    return exitcode;
}