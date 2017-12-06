//
// Created by Paul on 01.06.2017.
//

#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include "../../../include/sdl/utility/Path.h"
#include <utility/macros/OSDefines.h>

/*
 * Get the resource path for resources located in res/subDir
 * It's assumed the project directory is structured like:
 * bin/
 *  res/
 *  OS/ eg Windows or Linux
 *    debug/
 *      executable in here
 *    release/
 *      executable in here
 */
std::string getResourcePath() {
    //We need to choose the path separator properly based on which
    //platform we're running on, since Windows uses a different
    //separator than most systems
#ifdef PAX_OS_WIN
    const char PATH_SEP = '\\';
#else
    const char PATH_SEP = '/';
#endif

#ifdef PAX_OS_ANDROID
    return "res/";
#else
    //This will hold the base resource path: Lessons/res/
    //We give it static lifetime so that we'll only need to call
    //SDL_GetBasePath once to get the executable path
    static std::string baseRes;
    if (baseRes.empty()){
        //SDL_GetBasePath will return NULL if something went wrong in retrieving the path
        char *basePath = SDL_GetBasePath();
        if (basePath){
            baseRes = basePath;
            SDL_free(basePath);
        }
        else {
            std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
            return "";
        }
        //We replace the last bin/ with res/ to get the the resource path
        //size_t pos = baseRes.rfind("bin");
        //baseRes = baseRes.substr(0, pos) + "res" + PATH_SEP;
        baseRes = baseRes + ".." + PATH_SEP + ".." + PATH_SEP + "res" + PATH_SEP;
    }
    //If we want a specific subdirectory path in the resource directory
    //append it to the base path. This would be something like Lessons/res/Lesson0
    return baseRes;
#endif
}