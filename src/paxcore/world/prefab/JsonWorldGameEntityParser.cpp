//
// Created by Paul on 22.06.2019.
//

#include <paxcore/world/prefab/JsonWorldGameEntityParser.h>
#include <polypropylene/serialisation/json/JsonDefaultParsers.h>

namespace PAX {
    namespace Json {
        JsonWorldGameEntityParser::~JsonWorldGameEntityParser() = default;

        void JsonWorldGameEntityParser::parse(nlohmann::json &node, World & w,
                                              PAX::Json::JsonEntityPrefab<PAX::World> &prefab,
                                              const VariableRegister & v) {
            if (!node.is_array())
                PAX_LOG(Log::Level::Warn, "Given node is not an array!");

            for (const auto & el : node.items()) {
                nlohmann::json & entityNode = el.value();

                /// TODO: Parse name!?

                GameEntity * entity = nullptr;
                if (entityNode.count("prefab") > 0) {
                    nlohmann::json & prefabNode = entityNode["prefab"];

                    VariableRegister parameters = v;
                    if (entityNode.count("parameters") > 0) {
                        parameters = PAX::ComposeVariableRegisters(
                                parameters,
                                Json::tryParse<VariableRegister>(entityNode["parameters"]));
                    }

                    if (prefabNode.is_string()) {
                        std::shared_ptr<GameEntityPrefab> entityPrefab =
                                Services::GetResources().loadOrGet<GameEntityPrefab>(prefab.resolvePath(prefabNode.get<std::string>()));
                        entity = entityPrefab->create(parameters);
                    } else {
                        JsonEntityPrefab<GameEntity> entityPrefab(prefabNode, prefab.getPath());
                        entity = entityPrefab.create(parameters);
                    }
                } else {
                    entity = pax_new(GameEntity)();
                }

                if (entityNode.count("id") > 0) {
                    auto id = entityNode["id"].get<GameEntityID>();
                    w.getGameEntityIDService().reserveIDFor(entity, id);
                }

                w.spawn(entity);
            }
        }
    }
}