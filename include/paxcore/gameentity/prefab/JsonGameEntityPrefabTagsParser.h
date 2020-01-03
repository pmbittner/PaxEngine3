//
// Created by Paul on 03.11.2019.
//

#ifndef PAXENGINE3_JSONENTITYPREFABTAGSPARSER_H
#define PAXENGINE3_JSONENTITYPREFABTAGSPARSER_H

#include <paxcore/entity/GameEntity.h>
#include <polypropylene/property/construction/json/JsonPropertyContainerPrefab.h>

namespace PAX {
    class JsonGameEntityPrefabTagsParser : public Json::JsonPropertyContainerPrefabElementParser<GameEntity> {
    public:
        void parse(
                nlohmann::json & node,
                GameEntity & e,
                Json::JsonPropertyContainerPrefab<GameEntity> & prefab,
                const VariableRegister & v) override;
    };
}

#endif //PAXENGINE3_JSONENTITYPREFABTAGSPARSER_H
