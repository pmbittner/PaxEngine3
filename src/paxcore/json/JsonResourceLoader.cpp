//
// Created by Bittner on 04.01.2020.
//

#include <paxcore/json/JsonResourceLoader.h>
#include <paxutil/io/FileTypeChecker.h>
#include "polypropylene/serialisation/json/JsonLoader.h"
#include "polypropylene/serialisation/json/nlohmann/Json.h"

namespace PAX {
    bool JsonResourceLoader::canLoad(PAX::Path p) const {
        return Util::FileTypeChecker({"json"}).check(p);
    }

    std::shared_ptr<nlohmann::json> JsonResourceLoader::load(Path p) {
        Json::JsonLoader l;
        return std::make_shared<nlohmann::json>(l.load(p));
    }
}