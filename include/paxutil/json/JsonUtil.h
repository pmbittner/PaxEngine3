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
        virtual ~JsonElementParser() = 0;
        virtual void parse(nlohmann::json &, Args...) = 0;
    };
}

#endif //PAXENGINE3_JSONUTIL_H
