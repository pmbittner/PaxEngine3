//
// Created by Paul on 03.11.2019.
//

#include <paxcore/gameentity/prefab/JsonGameEntityPrefabTagsParser.h>

namespace PAX {
    void JsonGameEntityPrefabTagsParser::parse(
            nlohmann::json &node,
            GameEntity &e,
            Json::JsonEntityPrefab<GameEntity> &prefab,
            const VariableRegister &v)
    {
        if (node.is_array()) {
            for (auto & element : node) {
                e.addTag(JsonToString(element));
            }
        } else {
            PAX_THROW_RUNTIME_ERROR("Json element \"Tags\" is not an array!");
        }
    }
}