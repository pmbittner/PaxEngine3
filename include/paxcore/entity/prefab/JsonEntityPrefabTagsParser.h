//
// Created by Paul on 03.11.2019.
//

#ifndef PAXENGINE3_JSONENTITYPREFABTAGSPARSER_H
#define PAXENGINE3_JSONENTITYPREFABTAGSPARSER_H

#include <paxcore/entity/Entity.h>
#include <paxutil/property/construction/json/JsonPropertyContainerPrefab.h>

namespace PAX {
    class JsonEntityPrefabTagsParser : public Json::JsonPropertyContainerPrefabElementParser<Entity> {
    public:
        void parse(
                nlohmann::json & node,
                Entity & e,
                Json::JsonPropertyContainerPrefab<Entity> & prefab,
                const VariableRegister & v) override;
    };
}

#endif //PAXENGINE3_JSONENTITYPREFABTAGSPARSER_H
