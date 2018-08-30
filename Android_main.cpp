#define GL_GLEXT_PROTOTYPES 
#include <SDL.h> // Needs to be included, so SDL_main will be found.

#include "PaxEngineIncludes.h"
#include "include/EngineMain.h"

#define APPNAME "SDL"

// already defined by NDK
//#define ANDROID

int SDL_main(int argc, char **argv)
{
    return PAX::Engine_Main(argc, argv);
}