//
// Created by Paul on 19.12.2017.
//

#ifndef PAXENGINE3_COMPILERDETECTION_H
#define PAXENGINE3_COMPILERDETECTION_H

#if defined(__clang__)
#define PAX_COMPILER_CLANG
#elif defined(__GNUC__) || defined(__GNUG__)
#define PAX_COMPILER_GCC
#elif defined(_MSC_VER)
#define PAX_COMPILER_MSVC
#endif

#endif //PAXENGINE3_COMPILERDETECTION_H
