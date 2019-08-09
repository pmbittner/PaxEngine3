//
// Created by Bittner on 01/03/2019.
//

#ifndef PAXENGINE3_JSONUTIL_H
#define PAXENGINE3_JSONUTIL_H

#include "Json.h"

namespace PAX {
    template<typename... Args>
    class JsonElementParser {
    protected:
    public:
        virtual ~JsonElementParser() {};
        virtual void parse(nlohmann::json &, Args...) = 0;
    };

    std::string JsonToString(const nlohmann::json & j);
    nlohmann::json StringToJson(const std::string & s);
}

#endif //PAXENGINE3_JSONUTIL_H
