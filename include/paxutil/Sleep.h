//
// Created by Paul on 28.04.2017.
//

#ifndef PAXENGINE3_SLEEP_H
#define PAXENGINE3_SLEEP_H

#include <paxutil/macros/OSDetection.h>

#if defined(PAX_OS_LINUX) || defined(PAX_OS_ANDROID)
#include <unistd.h>
#elif defined(PAX_OS_WIN)
#include <windows.h>
#endif

namespace PAX {
    void ThreadSleep(unsigned int milliseconds) {
#if defined(PAX_OS_LINUX) || defined(PAX_OS_ANDROID)
        // usleep takes sleep time in microseconds (1 millionth of a second, 1 thousandth of a millisecond)
        usleep(milliseconds * 1000);
#elif defined(PAX_OS_WIN)
        Sleep(milliseconds);
#endif
    }
}

#endif //PAXENGINE3_SLEEP_H
