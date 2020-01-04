//
// Created by Bittner on 04.01.2020.
//

#ifndef PAXENGINE3_JSONENTITYPREFABRESOURCELOADER_H
#define PAXENGINE3_JSONENTITYPREFABRESOURCELOADER_H

#include <polypropylene/io/Path.h>
#include <polypropylene/property/EntityPrefab.h>
#include <paxutil/resources/ResourceLoader.h>
#include <paxutil/io/FileTypeChecker.h>
#include <polypropylene/serialisation/json/property/JsonEntityPrefabLoader.h>

namespace PAX {
    template<typename EntityType>
    class JsonEntityPrefabResourceLoader : public ResourceLoader<EntityPrefab<EntityType>, Path> {
        Json::JsonEntityPrefabLoader<EntityType> loader;

    public:
        PAX_NODISCARD bool canLoad(Path p) const override {
            return Util::FileTypeChecker({"json"}).check(p);
        }

        PAX_NODISCARD std::shared_ptr<EntityPrefab<EntityType>> load(Path p) override {
            return std::make_shared(loader.load(p));
        }
    };
}

#endif //PAXENGINE3_JSONENTITYPREFABRESOURCELOADER_H
