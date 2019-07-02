//
// Created by Paul on 02.07.2019.
//

#include <paxutil/json/JsonUtil.h>
#include <sstream>

namespace PAX {
    std::string JsonToString(const nlohmann::json & j) {
        if (j.is_string()) {
            return j;
        }

        /*
        //std::cout << "[JsonToString] " << key << " -> ";
        std::stringstream ss;
        ss << j;
        //std::cout << ss.str() << std::endl;
        return ss.str();
         */
        return j.dump();
    }
}