//
// Created by Bittner on 01/04/2019.
//

#include <paxcore/world/prefab/JsonWorldLayerPrefabInitParser.h>

namespace PAX {
    namespace Json {
        JsonWorldLayerPrefabInitParser::~JsonWorldLayerPrefabInitParser() = default;

        void JsonWorldLayerPrefabInitParser::parse(nlohmann::json &node, PAX::WorldLayer &c,
                                                   PAX::Json::JsonEntityPrefab<PAX::WorldLayer> &prefab,
                                                   const VariableRegister & v) {
            const std::string & name = node["name"];
            int dimensions = node["dimensions"];
            float z = node["z"];

            // TODO: Custom SceneGraphGenerator is not supported, yet.
            c.initialize(name, dimensions, z);
        }
    }
}