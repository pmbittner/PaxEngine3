//
// Created by Bittner on 01/03/2019.
//

#ifndef PAXENGINE3_JSONLOADER_H
#define PAXENGINE3_JSONLOADER_H

#include <paxutil/resources/ResourceLoader.h>
#include "Json.h"

namespace PAX {
    namespace Json {
        class JsonLoader : public ResourceLoader<nlohmann::json, Path> {
        public:
            std::shared_ptr<nlohmann::json> loadToOrGetFromResources(Resources &resources, const VariableHierarchy &parameters) override;
            bool canLoad(Path) const override;
            std::shared_ptr<nlohmann::json> load(Path) override;
        };
    }
}

#endif //PAXENGINE3_JSONLOADER_H
