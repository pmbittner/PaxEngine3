//
// Created by Paul on 02.06.2017.
//

#ifndef PAXENGINE3_MACROINCLUDES_H
#define PAXENGINE3_MACROINCLUDES_H

/** UTILITY **/

#include <stdexcept>

#define PAX_typeof(expr) std::type_index(typeid(expr))
#define PAX_nameof(type) #type

#define PAX_assertNotNull(value, str_message) if (value == nullptr) throw std::invalid_argument(str_message);

/** MATH **/

#define _USE_MATH_DEFINES
#include <cmath>
#ifndef M_PI
#include <math.h>
#endif
#ifdef M_PI
#define PAX_PI M_PI
#else
#define PAX_PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679
#endif
#undef _USE_MATH_DEFINES

#define PAX_ToRadians(degrees) (degrees * M_PI / 180.0)
#define PAX_ToDegrees(radians) (radians * 180 / M_PI)

#endif //PAXENGINE3_MACROINCLUDES_H
