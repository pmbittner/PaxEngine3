//
// Created by Bittner on 01/03/2019.
//

#ifndef PAXENGINE3_JSONPROPERTYCONTAINERPREFABLOADER_H
#define PAXENGINE3_JSONPROPERTYCONTAINERPREFABLOADER_H

#include <paxutil/resources/ResourceLoader.h>
#include <paxutil/io/Path.h>
#include <paxutil/io/FileTypeChecker.h>
#include <paxutil/resources/Resources.h>

#include "JsonPropertyContainerPrefab.h"

namespace PAX {
    namespace Json {
        template<typename C>
        class JsonPropertyContainerPrefabLoader : public ResourceLoader<PropertyContainerPrefab<C>, Path> {
            Resources &resources;

        public:
            /**
             * As the Prefabs will be loaded from JSON files, a ResourceManager is required, that is able
             * to load JSON files.
             * The <paxutil/json/JsonLoader.h> can be used therefore.
             */
            explicit JsonPropertyContainerPrefabLoader(Resources &resources) : resources(resources) {}

            bool canLoad(Path path) const override {
                return Util::FileTypeChecker({"paxprefab.json"}).check(path);
            }

            std::shared_ptr<PropertyContainerPrefab<C>> load(Path path) override {
                std::shared_ptr<nlohmann::json> j = resources.loadOrGet<nlohmann::json>(path);
                if (j) {
                    return std::make_shared<JsonPropertyContainerPrefab<C>>(j, path);
                }
                return nullptr;
            }

            std::shared_ptr<PropertyContainerPrefab<C>>
            loadToOrGetFromResources(Resources &resources, const VariableHierarchy &parameters) override {
                PAX_NOT_IMPLEMENTED_EXCEPTION()
            }
        };
    }
}

#endif //PAXENGINE3_JSONPROPERTYCONTAINERPREFABLOADER_H
