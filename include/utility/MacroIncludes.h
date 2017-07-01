//
// Created by Paul on 02.06.2017.
//

#ifndef PAXENGINE3_MACROINCLUDES_H
#define PAXENGINE3_MACROINCLUDES_H

/** UTILITY **/

#define PAX_typeof(expr) std::type_index(typeid(expr))
#define PAX_nameof(type) std::type_index(typeid(type)).name()

#define PAX_assertNotNull(value, str_message) if (value == nullptr) throw std::invalid_argument(str_message);

typedef unsigned int uint;

/** MATH **/

#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

#define PAX_ToRadians(degrees) (degrees * M_PI / 180.0)
#define PAX_ToDegrees(radians) (radians * 180 / M_PI)

#endif //PAXENGINE3_MACROINCLUDES_H
