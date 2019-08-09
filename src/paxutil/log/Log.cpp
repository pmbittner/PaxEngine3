//
// Created by Bittner on 03.04.2019.
//

#include <paxutil/log/Log.h>
#include <iostream>
#include <chrono>
#include <ctime>
#include <sstream>

namespace PAX {
    Log Log::instance = Log();

    std::ostream * Log::getStreamFor(PAX::Log::Level level) {
        if (level <= currentLevel) {
            return outstreams.at(level);
        } else {
            return &nullStream;
        }
    }

    Log::Log() : nullStream(&nullBuffer) {
        outstreams[Level::None] = &nullStream;

        outstreams[Level::Error] = &std::cerr;
        outstreams[Level::Warn] = &std::cerr;

        outstreams[Level::Info] = &std::cout;
        outstreams[Level::Debug] = &std::cout;
        outstreams[Level::Verbose] = &std::cout;
    }

    std::string Log::timestamp() {
        std::time_t t = std::time(nullptr);
        std::tm* now = std::localtime(&t);
        std::stringstream s;
        s << 1900 + now->tm_year << "/" << 1 + now->tm_mon << "/" << now->tm_mday << " " << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec;
        return s.str();
    }

    std::ostream & Log::stream(Level level, const char * functionName, const char * fileName, int line) {
        std::ostream & stream = *getStreamFor(level);
        stream << timestamp() << " " << level << " [" << (functionName ? functionName : "unknown") << "] ";
        if (level == Level::Warn || level == Level::Error || level == Level::Debug) {
            stream << fileName << "(" << line << "): ";
        }
        return stream;
    }

    std::ostream & Log::stream_raw(Level level) {
        return *getStreamFor(level);
    }
}

std::ostream& operator<<(std::ostream& os, const ::PAX::Log::Level & level) {
    using namespace ::PAX;
    switch (level) {
        case Log::Level::None: {
            return os;
        }
        case Log::Level::Error: {
            return os << "ERROR";
        }
        case Log::Level::Warn: {
            return os << "WARNING";
        }
        case Log::Level::Info: {
            return os << "INFO";
        }
        case Log::Level::Debug: {
            return os << "DEBUG";
        }
        case Log::Level::Verbose: {
            return os << "VERBOSE";
        }
        default: {
            return os << "<UNKNOWN LOG LEVEL>";
        }
    }
}