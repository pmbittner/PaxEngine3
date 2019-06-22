//
// Created by Paul on 02.06.2017.
//

#ifndef PAXENGINE3_MACROINCLUDES_H
#define PAXENGINE3_MACROINCLUDES_H

#include "CompilerDetection.h"
#include <sstream>
#include <ostream>
#include <stdexcept>
#include "../log/Log.h"

/** UTILITY **/
// We do not use a template function here to avoid multiple instanciation of the same function
// and thus keep the code smaller and inlined.
#define PAX_assertNotNull(value, ...) { \
if (value == nullptr) { \
    std::stringstream s; \
    s << __VA_ARGS__; \
    Log::out.err() << s.str() << std::endl; \
    throw std::invalid_argument(s.str()); \
}}

#define PAX_THROW_RUNTIME_ERROR(...) { \
    std::stringstream s; \
    s << __VA_ARGS__; \
    PAX_PRINT_ERR(s.str()) \
    throw std::runtime_error(s.str()); \
}

#endif //PAXENGINE3_MACROINCLUDES_H
