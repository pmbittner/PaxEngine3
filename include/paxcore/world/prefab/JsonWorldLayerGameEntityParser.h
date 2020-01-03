//
// Created by Paul on 22.06.2019.
//

#ifndef PAXENGINE3_JSONWORLDLAYERGAMEENTITYPARSER_H
#define PAXENGINE3_JSONWORLDLAYERGAMEENTITYPARSER_H

#include <paxcore/world/WorldLayer.h>
#include <polypropylene/property/construction/json/JsonPropertyContainerPrefab.h>

namespace PAX {
    namespace Json {
        class JsonWorldLayerGameEntityParser : public JsonPropertyContainerPrefabElementParser<WorldLayer> {
        public:
            ~JsonWorldLayerGameEntityParser() override;
            void parse(nlohmann::json & node, WorldLayer & c, JsonPropertyContainerPrefab<WorldLayer> & prefab, const VariableRegister & v) override;
        };
    }
}

#endif //PAXENGINE3_JSONWORLDLAYERGAMEENTITYPARSER_H
