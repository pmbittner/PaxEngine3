//
// Created by Paul on 02.06.2017.
//

#ifndef PAXENGINE3_MACROINCLUDES_H
#define PAXENGINE3_MACROINCLUDES_H

#include "CompilerDetection.h"

/** UTILITY **/

#define PAX_assertNotNull(value, str_message) if (value == nullptr) throw std::invalid_argument(str_message);

#endif //PAXENGINE3_MACROINCLUDES_H
