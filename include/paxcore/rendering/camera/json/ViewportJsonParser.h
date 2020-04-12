//
// Created by Bittner on 21.02.2020.
//

#ifndef PAXENGINE3_VIEWPORTJSONPARSER_H
#define PAXENGINE3_VIEWPORTJSONPARSER_H

#include <polypropylene/serialisation/json/JsonParser.h>
#include "paxcore/rendering/camera/Viewport.h"

namespace PAX {
    template<>
    class TryParser<nlohmann::json, Viewport*> {
    public:
        PAX_NODISCARD static Viewport * tryParse(const nlohmann::json & j);
    };
}

#endif //PAXENGINE3_VIEWPORTJSONPARSER_H
