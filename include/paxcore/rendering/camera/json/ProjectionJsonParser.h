//
// Created by Bittner on 21.02.2020.
//

#ifndef PAXENGINE3_PROJECTIONJSONPARSER_H
#define PAXENGINE3_PROJECTIONJSONPARSER_H

#include <polypropylene/serialisation/json/JsonParser.h>
#include "../Projection.h"

namespace PAX {
    template<>
    class TryParser<nlohmann::json, Projection*> {
    public:
        PAX_NODISCARD static Projection * tryParse(const nlohmann::json & j);
    };
}

#endif //PAXENGINE3_PROJECTIONJSONPARSER_H
