//
// Created by Paul on 03.11.2019.
//

#include <paxcore/entity/prefab/JsonGameEntityPrefabTagsParser.h>

namespace PAX {
    void JsonGameEntityPrefabTagsParser::parse(
            nlohmann::json &node,
            PAX::GameEntity &e,
            PAX::Json::JsonPropertyContainerPrefab<PAX::GameEntity> &prefab,
            const PAX::VariableRegister &v)
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