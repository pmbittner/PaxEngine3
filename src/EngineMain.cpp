//
// Created by Paul on 29.04.2017.
//

#include <easylogging++.h>

#include <demo/OpenGL/TerrainDemo.h>
#include <demo/Platformer/PlatformerDemo.h>
#include <sdl/opengl/SDLOpenGLEnginePlugin.h>

#include <EngineMain.h>

#include <sdl/SDLEnginePlugin.h>
#include <opengl/OpenGLEnginePlugin.h>
#include <opengl/OpenGL2DEnginePlugin.h>
#include <sdl/opengl/SDLOpenGLEngineSetup.h>

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