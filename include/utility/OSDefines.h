//
// Created by Paul on 28.04.2017.
//

#ifndef PAXENGINE3_OSDEFINES_H
#define PAXENGINE3_OSDEFINES_H

#if defined (__linux__) || defined(linux) || defined(LINUX)
#define PAX_OS_LINUX

#elif defined (__unix__) || defined(UNIX)
#define PAX_OS_UNIX

#elif defined(WINDOWS) || defined(WIN32) ||  defined(_WIN32) || defined(__WIN32__)
#define PAX_OS_WIN

#elif defined(ANDROID)
#define PAX_OS_ANDROID
#endif

#if defined(PAX_OS_WIN) ^ defined(PAX_OS_LINUX) ^ defined(PAX_OS_ANDROID) ^ defined(PAX_OS_UNIX)
#else
#error "No or multiple operating systems declared!"
#endif

//#ifdef PAX_OS_WIN
//#define PAX_GFX_DIRECTX
//#else
#define PAX_GFX_OPENGL
//#endif

#endif //PAXENGINE3_OSDEFINES_H
