//
// Created by Bittner on 21/05/2019.
//

#ifndef PAXENGINE3_JSONPARSER_H
#define PAXENGINE3_JSONPARSER_H

#include "Json.h"
#include "../TryParser.h"

namespace PAX {
    template<class To>
    class TryParser<nlohmann::json, To> {
    public:
        [[nodiscard]] static To tryParse(const nlohmann::json & f) {
            return String::tryParse<To>(f);
        }
    };

    namespace Json {
        template<typename T>
        T tryParse(const nlohmann::json & j) {
            return TryParser<nlohmann::json, T>::tryParse(j);
        }
    }

#define PAX_SPECIALIZE_JSONTRYPARSE_HEADER(type) \
            template<> \
            class TryParser<nlohmann::json, type> { \
            public: \
                [[nodiscard]] static type tryParse(const std::string & str); \
            };
}

#endif //PAXENGINE3_JSONPARSER_H
