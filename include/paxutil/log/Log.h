//
// Created by Bittner on 03.04.2019.
//

#ifndef PAXENGINE3_LOG_H
#define PAXENGINE3_LOG_H

#include "../macros/OSDetection.h"
#include "../macros/Definitions.h"
#include <ostream>
#include <map>

namespace PAX {
    class Log {
    public:
        enum class Level {
            None = 0,
            Error,
            Warn,
            Info,
            Debug,
            Verbose
        };

    private:
        class NullBuffer : public std::streambuf {
        public:
            int overflow(int c) { return c; }
        } nullBuffer;
        std::ostream nullStream;

        std::map<Level, std::ostream*> outstreams;
        std::ostream * getStreamFor(Level level);

    public:
        static Log instance;
        static std::string timestamp();

#ifdef PAX_BUILD_TYPE_DEBUG
        Level currentLevel = Level::Debug;
#else
        Level currentLevel = Level::Error;
#endif

        Log();

        std::ostream & stream(Level level, const char * functionName = nullptr, const char * fileName = nullptr, int line = 0);
        std::ostream & stream_raw(Level level);
    };

// TODO: What about __func__ ?
#ifdef PAX_OS_WIN
#define PAX_FUNCTION_NAME __FUNCTION__
#else
#define PAX_FUNCTION_NAME __PRETTY_FUNCTION__
#endif

#define ___PAX_LOG_IMPL(level, stream, message)
#define PAX_LOG(level, message) do {::PAX::Log::instance.stream(level, PAX_FUNCTION_NAME, __FILE__, __LINE__) << message << std::endl;} while(0)
#define PAX_LOG_RAW(level, message) do {::PAX::Log::instance.stream_raw(level) << message << std::endl;} while(0)

#ifdef PAX_BUILD_TYPE_DEBUG
    #define PAX_LOG_DEBUG(level, message) PAX_LOG(level, message)
#elif defined(PAX_BUILD_TYPE_RELEASE)
    #define PAX_LOG_DEBUG(level, message) do {} while(0)
#endif
}

std::ostream& operator<<(std::ostream& os, const ::PAX::Log::Level & level);

#endif //PAXENGINE3_LOG_H
