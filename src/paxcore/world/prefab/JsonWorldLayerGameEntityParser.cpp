//
// Created by Paul on 22.06.2019.
//

#include <paxcore/world/prefab/JsonWorldLayerGameEntityParser.h>

namespace PAX {
    namespace Json {
        JsonWorldLayerGameEntityParser::~JsonWorldLayerGameEntityParser() = default;

        void JsonWorldLayerGameEntityParser::parse(nlohmann::json &node, PAX::WorldLayer & worldLayer,
                                               PAX::Json::JsonPropertyContainerPrefab<PAX::WorldLayer> &prefab,
                                               const VariableRegister & v) {
            if (!node.is_array())
                PAX_LOG(Log::Level::Warn, "Given node is not an array!");

            for (const auto & el : node.items()) {
                nlohmann::json & entityNode = el.value();

                /// TODO: Parse name!?

                GameEntity * entity = nullptr;
                if (entityNode.count("prefab") > 0) {
                    nlohmann::json & prefabNode = entityNode["prefab"];

                    if (prefabNode.is_string()) {
                        std::shared_ptr<GameEntityPrefab> entityPrefab =
                                Services::GetResources().loadOrGet<GameEntityPrefab>(prefab.resolvePath(prefabNode.get<std::string>()));
                        entity = entityPrefab->create({});
                    } else {
                        JsonPropertyContainerPrefab<GameEntity> entityPrefab(
                                std::shared_ptr<nlohmann::json>(
                                        &prefabNode,
                                        [](nlohmann::json*){
                                            // Nothing to do here:
                                            // We only need this shared_ptr as a wrapper
                                            // for prefab construction.
                                        }
                                        ),
                                prefab.getPath());
                        entity = entityPrefab.create({});
                    }
                } else {
                    // TODO: Write GameEntityAllocator
                    entity = new GameEntity();
                }

                if (entityNode.count("id") > 0) {
                    GameEntityID id = entityNode["id"].get<GameEntityID>();
                    worldLayer.getGameEntityIDService().reserveIDFor(entity, id);
                }

                worldLayer.spawn(entity);
            }
        }
    }
}