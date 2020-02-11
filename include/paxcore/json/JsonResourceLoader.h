//
// Created by Bittner on 04.01.2020.
//

#ifndef PAXENGINE3_JSONRESOURCELOADER_H
#define PAXENGINE3_JSONRESOURCELOADER_H

#include <polypropylene/serialisation/json/JsonFwd.h>
#include "paxutil/resources/ResourceLoader.h"

namespace PAX {
    class JsonResourceLoader : public ResourceLoader<nlohmann::json, Path> {
    public:
        PAX_NODISCARD std::shared_ptr<nlohmann::json> loadOrGetFromJson(Resources & resources, const nlohmann::json & j) const override;

        PAX_NODISCARD bool canLoad(Path p) const override;
        PAX_NODISCARD std::shared_ptr<nlohmann::json> load(Path p) override;
    };
}

#endif //PAXENGINE3_JSONRESOURCELOADER_H
