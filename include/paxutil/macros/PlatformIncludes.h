//
// Created by Paul on 01.09.2018.
//

#ifndef PAXENGINE3_PLATFORMINCLUDES_H
#define PAXENGINE3_PLATFORMINCLUDES_H

#include "polypropylene/definitions/OSDetection.h"

#ifdef PAX_OS_WIN
    // Disable min and max macros in windows.h as they conflict with std functions min/max and glm
    #ifndef NOMINMAX
        #define NOMINMAX
    #endif
#endif

#endif //PAXENGINE3_PLATFORMINCLUDES_H
