//
// Created by Paul on 03.11.2019.
//

#ifndef PAXENGINE3_JSONENTITYPREFABTAGSPARSER_H
#define PAXENGINE3_JSONENTITYPREFABTAGSPARSER_H

#include <paxcore/gameentity/GameEntity.h>
#include <polypropylene/serialisation/json/property/JsonEntityPrefab.h>

namespace PAX {
    class JsonGameEntityPrefabTagsParser : public Json::JsonEntityPrefabElementParser<GameEntity> {
    public:
        void parse(
                nlohmann::json & node,
                GameEntity & e,
                Json::JsonEntityPrefab<GameEntity> & prefab,
                const VariableRegister & v) override;
    };
}

#endif //PAXENGINE3_JSONENTITYPREFABTAGSPARSER_H
