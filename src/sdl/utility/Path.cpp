//
// Created by Paul on 01.06.2017.
//

#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include "../../../include/sdl/utility/Path.h"
#include <utility/macros/OSDefines.h>
#include <core/service/Paths.h>
#include <lib/easylogging++.h>

namespace PAX {
    namespace SDL {
        std::string getBasePath() {
            //We need to choose the path separator properly based on which
            //platform we're running on, since Windows uses a different
            //separator than most systems
#ifdef PAX_OS_WIN
            const char PATH_SEP = '\\';
#else
            const char PATH_SEP = '/';
#endif
            //This will hold the base resource path: Lessons/res/
            //We give it static lifetime so that we'll only need to call
            //SDL_GetBasePath once to get the executable path
            static std::string baseRes;
            if (baseRes.empty()) {
                char *basePath = SDL_GetBasePath();
                if (basePath) {
                    baseRes = basePath;
                    SDL_free(basePath);
                } else {
                    LOG(ERROR) << "Error getting resource path: " << SDL_GetError();
                    return "";
                }
            }
            return baseRes;
        }
    }
}