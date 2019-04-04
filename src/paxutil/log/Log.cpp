//
// Created by Bittner on 03.04.2019.
//

#include <paxutil/log/Log.h>
#include <iostream>
#include <chrono>
#include <ctime>
#include <sstream>

namespace PAX {
    Log Log::cout = Log(std::cout, std::cerr);

    Log::Log(std::ostream &out, std::ostream &err) : out_stream(out), err_stream(err) {

    }

    std::string Log::timestamp() {
        std::time_t t = std::time(nullptr);
        std::tm* now = std::localtime(&t);
        std::stringstream s;
        s << 1900 + now->tm_year << "/" << 1 + now->tm_mon << "/" << now->tm_mday << " " << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec;
        return s.str();
    }

    std::ostream& Log::info() {
        return out_stream << timestamp() << " ";
    }

    std::ostream& Log::err() {
        return err_stream << timestamp() << " ";
    }

    std::ostream& Log::info_raw() {
        return out_stream;
    }

    std::ostream& Log::err_raw() {
        return err_stream;
    }
}