//
// Created by Bittner on 03.04.2019.
//

#ifndef PAXENGINE3_LOG_H
#define PAXENGINE3_LOG_H

#include "../macros/OSDetection.h"
#include <ostream>

namespace PAX {
    class Log {
        std::ostream & out_stream;
        std::ostream & err_stream;

    public:
        static Log cout;
        static std::string timestamp();

        Log(std::ostream & out, std::ostream & err);

        std::ostream & info();
        std::ostream & err();

        std::ostream & info_raw();
        std::ostream & err_raw();
    };

// TODO: What about __func__ ?
#ifdef PAX_OS_WIN
#define PAX_FUNCTION_NAME __FUNCTION__
#else
#define PAX_FUNCTION_NAME __PRETTY_FUNCTION__
#endif

#define PAX_PRINT_TO(stream, message) {stream << "[" << PAX_FUNCTION_NAME << "] " << message  << std::endl;}
#define PAX_PRINT_OUT(message) PAX_PRINT_TO(::PAX::Log::cout.info(), message)
#define PAX_PRINT_ERR(message) PAX_PRINT_TO(::PAX::Log::cout.err(), __FILE__ << "(" << __LINE__ << "): " << message)

#ifdef PAX_BUILD_TYPE_DEBUG
    #define PAX_PRINT_TO_DEBUG(stream, message) PAX_PRINT_TO(stream, message)
    #define PAX_PRINT_OUT_DEBUG(message) PAX_PRINT_OUT(stream, message)
    #define PAX_PRINT_ERR_DEBUG(message) PAX_PRINT_ERR(stream, message)
#elif defined(PAX_BUILD_TYPE_RELEASE)
    #define PAX_PRINT_TO_DEBUG(stream, message)
    #define PAX_PRINT_OUT_DEBUG(message)
    #define PAX_PRINT_ERR_DEBUG(message)
#endif
}

#endif //PAXENGINE3_LOG_H
