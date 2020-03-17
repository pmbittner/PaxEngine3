//
// Created by Bittner on 01/04/2019.
//

#include <paxcore/world/prefab/JsonWorldPrefabInitParser.h>

namespace PAX {
    namespace Json {
        JsonWorldPrefabInitParser::~JsonWorldPrefabInitParser() = default;

        void JsonWorldPrefabInitParser::parse(nlohmann::json &node, World & w,
                                              PAX::Json::JsonEntityPrefab<PAX::World> &prefab,
                                              const VariableRegister & v) {
            const std::string & name = node["name"];
            int dimensions = node["dimensions"];
            float z = node["z"];

            // TODO: Custom SceneGraphGenerator is not supported, yet.
            w.initialize(name, dimensions, z);
        }
    }
}