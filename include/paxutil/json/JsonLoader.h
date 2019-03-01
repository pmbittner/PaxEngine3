//
// Created by Bittner on 01/03/2019.
//

#ifndef PAXENGINE3_JSONLOADER_H
#define PAXENGINE3_JSONLOADER_H

#include <paxcore/io/resources/ResourceLoader.h>
#include "Json.h"

namespace PAX {
    class JsonLoader : public ResourceLoader<nlohmann::json, Path> {
    public:
        bool canLoad(Path) const override;
        std::shared_ptr<nlohmann::json> load(Path) override;
    };
}

#endif //PAXENGINE3_JSONLOADER_H
