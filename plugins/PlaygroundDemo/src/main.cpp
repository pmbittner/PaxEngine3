//
// Created by Paul on 15.08.2018.
//

#define WITH_PAX_OPENGL2D

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
#ifdef WITH_PAX_OPENGL2D
#include <opengl/include/OpenGL2DEnginePlugin.h>
#endif
#include <PlaygroundDemo/include/Plugin.h>
#include <assetimport/include/Plugin.h>

int PAX::PlaygroundDemo_main(int argc, char *argv[]) {
    int exitcode = 0;

    PAX::PlaygroundDemo::Demo game;

    PAX::SDL::SDLEnginePlugin               sdl;
    PAX::OpenGL::OpenGLEnginePlugin         openGL;
#ifdef WITH_PAX_OPENGL2D
    /// TODO: Make Plugin obsolete by enhancing the relevant factory by a parameter for dimensions
    PAX::OpenGL::OpenGL2DEnginePlugin openGL2DFeatures;
#endif
    PAX::SDL::OpenGL::SDLOpenGLEnginePlugin sdlOpenGLLink;
    PAX::AssetImport::Plugin                     modelLoader;
    PAX::PlaygroundDemo::Plugin             demoPlugin;

    PAX::Engine &engine = PAX::Engine::Instance();
    engine.initialize(
            &game,
            {
                    &sdl,
                    &openGL,
#ifdef WITH_PAX_OPENGL2D
                    &openGL2DFeatures,
#endif
                    &sdlOpenGLLink,
                    &modelLoader,
                    &demoPlugin
            }
    );
    exitcode = engine.run();

    return exitcode;
}