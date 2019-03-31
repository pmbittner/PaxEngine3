//
// Created by Paul on 02.06.2017.
//

#ifndef PAXENGINE3_MACROINCLUDES_H
#define PAXENGINE3_MACROINCLUDES_H

#include "CompilerDetection.h"
#include <sstream>
#include <ostream>

/** UTILITY **/
// We do not use a template function here to avoid multiple instanciation of the same function
// and thus keep the code smaller and inlined.
#define PAX_assertNotNull(value, str_message) { \
if (value == nullptr) { \
    std::stringstream s; \
    s << str_message; \
    std::cerr << s.str() << std::endl; \
    throw std::invalid_argument(s.str()); \
}}

#endif //PAXENGINE3_MACROINCLUDES_H
