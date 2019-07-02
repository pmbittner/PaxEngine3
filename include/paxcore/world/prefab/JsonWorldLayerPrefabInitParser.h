//
// Created by Bittner on 01/04/2019.
//

#ifndef PAXENGINE3_JSONWORLDLAYERPREFABINITPARSER_H
#define PAXENGINE3_JSONWORLDLAYERPREFABINITPARSER_H

#include <paxcore/world/WorldLayer.h>
#include <paxutil/property/construction/json/JsonPropertyContainerPrefab.h>

namespace PAX {
    namespace Json {
        class JsonWorldLayerPrefabInitParser : public JsonPropertyContainerPrefabElementParser<WorldLayer> {
        public:
            ~JsonWorldLayerPrefabInitParser() override;
            void parse(nlohmann::json & node, WorldLayer & c, JsonPropertyContainerPrefab<WorldLayer> & prefab, const VariableRegister & v) override;
        };
    }
}

#endif //PAXENGINE3_JSONWORLDLAYERPREFABINITPARSER_H
