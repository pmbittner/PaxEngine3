//
// Created by Paul on 03.11.2019.
//

#include <paxcore/entity/prefab/JsonEntityPrefabTagsParser.h>

namespace PAX {
    void JsonEntityPrefabTagsParser::parse(
            nlohmann::json &node,
            PAX::Entity &e,
            PAX::Json::JsonPropertyContainerPrefab<PAX::Entity> &prefab,
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