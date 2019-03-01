//
// Created by Bittner on 01/03/2019.
//

#ifndef PAXENGINE3_JSONPROPERTYCONTAINERPREFABLOADER_H
#define PAXENGINE3_JSONPROPERTYCONTAINERPREFABLOADER_H

#include <paxcore/io/resources/ResourceLoader.h>
#include <paxutil/property/construction/PropertyContainerPrefab.h>
#include <paxutil/io/Path.h>

namespace PAX {
    template<typename C>
    class JsonPropertyContainerPrefabLoader : public ResourceLoader<PropertyContainerPrefab<C>, Path> {
    public:
        bool canLoad(Path path) const override {
            return Util::FileTypeChecker({"JSON"}).check(path);
        }

        std::shared_ptr<PropertyContainerPrefab<C>> load(Path path) override {
            // TODO: Find solution for Services being not part of paxutil but paxcore.
            std::shared_ptr<nlohmann::json> j = Services::GetResources().loadOrGet<nlohmann::json>(path);
            if (j) {
                return std::make_shared<JsonPropertyContainerPrefab>(j);
            }
            return nullptr;
        }
    };
}

#endif //PAXENGINE3_JSONPROPERTYCONTAINERPREFABLOADER_H
